load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# grpc 1.35.0
http_archive(
    name = "com_github_grpc_grpc",
    urls = [
        "https://github.com/grpc/grpc/archive/257d0045ab958eb767a3591c88e9d0c2bdf4b916.tar.gz",
    ],
    strip_prefix = "grpc-257d0045ab958eb767a3591c88e9d0c2bdf4b916",
)
load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")
grpc_deps()
load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")
grpc_extra_deps()

# code auto-completion
http_archive(
    name = "com_grail_bazel_compdb",
    strip_prefix = "bazel-compilation-database-master",
    urls = ["https://github.com/grailbio/bazel-compilation-database/archive/master.tar.gz"],
)

http_archive(
    name = "com_google_googletest",
    sha256 = "94c634d499558a76fa649edb13721dce6e98fb1e7018dfaeba3cd7a083945e91",
    strip_prefix = "googletest-release-1.10.0",
    urls = ["https://github.com/google/googletest/archive/release-1.10.0.zip"],
)