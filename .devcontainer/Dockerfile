FROM ubuntu:focal

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        cmake build-essential autoconf libtool pkg-config \
        autogen libtool automake curl git gdb ca-certificates \
        protobuf-compiler clang gnupg g++-8

WORKDIR /tmp

# Download bazel-3.7.1
RUN apt-get install -y build-essential openjdk-11-jdk python3 zip unzip \
    && export JAVA_HOME=/usr/lib/jvm/java-11-openjdk-amd64 \
    && update-alternatives --install /usr/bin/python python /usr/bin/python3 1 \
    && curl -SLO https://github.com/bazelbuild/bazel/releases/download/3.7.1/bazel-3.7.1-dist.zip \
    && unzip -q bazel-3.7.1-dist.zip -d bazel-3.7.1-dist \
    && rm bazel-3.7.1-dist.zip

# Compile and install bazel-3.7.1
RUN cd bazel-3.7.1-dist \
    && export JAVA_HOME=/usr/lib/jvm/java-11-openjdk-amd64 \
    && env EXTRA_BAZEL_ARGS="--host_javabase=@local_jdk//:jdk" bash ./compile.sh \
    && cp output/bazel /usr/local/bin

# Compile and install bazel-3.7.1 auto completion script
RUN cd bazel-3.7.1-dist \
    && /usr/local/bin/bazel build //scripts:bazel-complete.bash \
    && cp bazel-bin/scripts/bazel-complete.bash /etc/bash_completion.d/ \
    && echo "source /etc/bash_completion.d/bazel-complete.bash" >> /root/.bashrc

# https://github.com/grailbio/bazel-compilation-database/tree/0.4.5
RUN export INSTALL_DIR="/usr/local/bin" && export VERSION="0.4.5" \
    && cd ${INSTALL_DIR} \
    && curl -L "https://github.com/grailbio/bazel-compilation-database/archive/${VERSION}.tar.gz" | tar -xz \
    && ln -f -s "${INSTALL_DIR}/bazel-compilation-database-${VERSION}/generate.sh" bazel-compdb

# ### Install protobuf and grpc
# WORKDIR /tmp
# RUN git clone https://github.com/grpc/grpc.git
# WORKDIR /tmp/grpc
# RUN git checkout remotes/origin/v1.30.x
# RUN git submodule update --init

# WORKDIR /tmp/grpc/third_party/protobuf
# RUN git checkout remotes/origin/3.12.x
# RUN ./autogen.sh
# RUN ./configure CXXFLAGS=-fPIC --prefix=/usr/local/bin/protobuf/protobuf-dev
# RUN make -j4
# RUN make install

# WORKDIR /tmp/grpc/
# RUN export PKG_CONFIG_PATH=/usr/local/bin/protobuf/protobuf-dev/lib/pkgconfig:/usr/local/bin/grpc/grpc-dev/lib/pkgconfig
# RUN export PATH=/usr/local/bin/protobuf/protobuf-dev/bin:/usr/local/bin/grpc/grpc-dev/bin:$PATH
# RUN export LD_LIBRARY_PATH=/usr/local/bin/protobuf/protobuf-dev/lib:/usr/local/bin/grpc/grpc-dev/lib
# RUN EXTRA_LDFLAGS=-L/usr/local/bin/protobuf/protobuf-dev/lib make -j4
# RUN make prefix=/usr/local/bin/grpc/grpc-dev install

# RUN echo /usr/local/bin/protobuf/protobuf-dev/lib | tee -a /etc/ld.so.conf.d/grpc.conf \
#   && echo /usr/local/bin/grpc/grpc-dev/lib | tee -a /etc/ld.so.conf.d/grpc.conf \
#   && ldconfig

WORKDIR /workspace
ENTRYPOINT /bin/bash