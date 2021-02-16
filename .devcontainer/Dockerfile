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

# Compile and install gtest-1.10.0
RUN git clone -b release-1.10.0 https://github.com/google/googletest.git \
    && cd googletest && mkdir build && cd build && cmake .. && make install \
    && cd /tmp && rm -r googletest

# User setting
ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN groupadd --gid $USER_GID $USERNAME \
    && useradd -s /bin/bash --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME
