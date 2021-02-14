# Copyright 2020 the gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

licenses(["notice"])  # 3-clause BSD


load("@com_grail_bazel_compdb//:aspects.bzl", "compilation_database")
load("@com_github_grpc_grpc//bazel:grpc_build_system.bzl", "grpc_cc_binary", "grpc_cc_library", "grpc_cc_test", "grpc_package")


compilation_database(
    name = "example_compdb",
    targets = [
        "//protos:helloworld"
    ],
)

cc_binary(
    name = "greeter_client",
    srcs = ["greeter_client.cc"],
    defines = ["BAZEL_BUILD"],
    deps = [
        "@com_github_grpc_grpc//:grpc++",
        "//protos:helloworld",
    ],
)

cc_binary(
    name = "greeter_async_client",
    srcs = ["greeter_async_client.cc"],
    defines = ["BAZEL_BUILD"],
    deps = [
        "@com_github_grpc_grpc//:grpc++",
        "//protos:helloworld",
    ],
)

cc_binary(
    name = "greeter_async_client2",
    srcs = ["greeter_async_client2.cc"],
    defines = ["BAZEL_BUILD"],
    deps = [
        "@com_github_grpc_grpc//:grpc++",
        "//protos:helloworld",
    ],
)

cc_binary(
    name = "greeter_server",
    srcs = ["greeter_server.cc"],
    defines = ["BAZEL_BUILD"],
    deps = [
        "@com_github_grpc_grpc//:grpc++",
        "@com_github_grpc_grpc//:grpc++_reflection",
        "//protos:helloworld",
    ],
)

cc_binary(
    name = "greeter_async_server",
    srcs = ["greeter_async_server.cc"],
    defines = ["BAZEL_BUILD"],
    deps = [
        "@com_github_grpc_grpc//:grpc++",
        "//protos:helloworld",
    ],
)

grpc_cc_test(
    name = "greeter_client_test",
    srcs = ["greeter_client_test.cc"],
    deps = [
        "@com_github_grpc_grpc//:gpr",
        "@com_github_grpc_grpc//:grpc",
        "@com_github_grpc_grpc//:grpc++",
        "@com_github_grpc_grpc//:grpc++_test",
        "@com_github_grpc_grpc//test/core/util:grpc_test_util",
        "@com_github_grpc_grpc//test/cpp/util:test_util",
        "@com_google_googletest//:gtest",
        "//protos:helloworld",
    ],
)
