#include <climits>

#include <grpcpp/grpcpp.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/test/default_reactor_test_peer.h>

#include "protos/helloworld_mock.grpc.pb.h"
#include "test/core/util/port.h"
#include "test/core/util/test_config.h"

#include <grpcpp/test/mock_stream.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>

using helloworld::Greeter;
using helloworld::HelloRequest;
using helloworld::HelloReply;
using helloworld::MockGreeterStub;
using ::testing::_;
using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SaveArg;
using ::testing::SetArgPointee;
using ::testing::WithArg;

namespace grpc {
namespace testing {

namespace {
class FakeClient {
 public:
  explicit FakeClient(Greeter::StubInterface* stub) : stub_(stub) {}

  void DoSayHello() {
    ClientContext context;
    HelloRequest request;
    HelloReply response;
    request.set_name("hello world");
    Status s = stub_->SayHello(&context, request, &response);
    EXPECT_EQ(request.name(), response.message());
    EXPECT_TRUE(s.ok());
  }

  void ResetStub(Greeter::StubInterface* stub) { stub_ = stub; }
 private:
  Greeter::StubInterface* stub_;
};

class CallbackTestServiceImpl : public Greeter::ExperimentalCallbackService {
 public:
  experimental::ServerUnaryReactor* SayHello(
      experimental::CallbackServerContext* context,
      const HelloRequest* request, HelloReply* response) override {
    auto* reactor = context->DefaultReactor();
    if (request->name().length() > 0) {
      response->set_message(request->name());
      reactor->Finish(Status::OK);
    } else {
      reactor->Finish(Status(StatusCode::INVALID_ARGUMENT, "Invalid request"));
    }
    return reactor;
  }
};

class MockCallbackTest : public ::testing::Test {
 protected:
  CallbackTestServiceImpl service_;
  ServerContext context_;
};

TEST_F(MockCallbackTest, MockedCallSucceeds) {
  experimental::CallbackServerContext ctx;
  HelloRequest req;
  HelloReply resp;
  testing::DefaultReactorTestPeer peer(&ctx);

  req.set_name("ha ha, consider yourself mocked.");
  auto* reactor = service_.SayHello(&ctx, &req, &resp);
  EXPECT_EQ(reactor, peer.reactor());
  EXPECT_TRUE(peer.test_status_set());
  EXPECT_TRUE(peer.test_status().ok());
}

TEST_F(MockCallbackTest, MockedCallFails) {
  experimental::CallbackServerContext ctx;
  HelloRequest req;
  HelloReply resp;
  DefaultReactorTestPeer peer(&ctx);

  auto* reactor = service_.SayHello(&ctx, &req, &resp);
  EXPECT_EQ(reactor, peer.reactor());
  EXPECT_TRUE(peer.test_status_set());
  EXPECT_EQ(peer.test_status().error_code(), StatusCode::INVALID_ARGUMENT);
}

class TestServiceImpl : public Greeter::Service {
 public:
  Status SayHello(ServerContext* /*context*/, const HelloRequest* request,
              HelloReply* response) override {
    response->set_message(request->name());
    return Status::OK;
  }
};

class MockTest : public ::testing::Test {
 protected:
  MockTest() {}

  void SetUp() override {
    int port = grpc_pick_unused_port_or_die();
    server_address_ << "localhost:" << port;
    // Setup server
    ServerBuilder builder;
    builder.AddListeningPort(server_address_.str(),
                             InsecureServerCredentials());
    builder.RegisterService(&service_);
    server_ = builder.BuildAndStart();                             
  }

  void TearDown() override { server_->Shutdown(); }

  void ResetStub() {
    std::shared_ptr<Channel> channel = grpc::CreateChannel(
        server_address_.str(), InsecureChannelCredentials());
    stub_ = Greeter::NewStub(channel);
  }

  std::unique_ptr<Greeter::Stub> stub_;
  std::unique_ptr<Server> server_;
  std::ostringstream server_address_;
  TestServiceImpl service_;
};

// Do one real rpc and one mocked one
TEST_F(MockTest, SimpleRpc) {
  ResetStub();
  FakeClient client(stub_.get());
  client.DoSayHello();
  helloworld::MockGreeterStub stub;
  HelloReply resp;
  resp.set_message("hello world");
  EXPECT_CALL(stub, SayHello(_, _, _))
      .Times(AtLeast(1))
      .WillOnce(DoAll(SetArgPointee<2>(resp), Return(Status::OK)));
  client.ResetStub(&stub);
  client.DoSayHello();
}


}  // namespace
}  // namespace testing
}  // namespace grpc


int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}