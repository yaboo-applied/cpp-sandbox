load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# grpc
http_archive(
    name = "com_github_grpc_grpc",
    urls = [
        "https://github.com/grpc/grpc/archive/a2f731fc48581401776582489d80d4622c8aa536.tar.gz",
    ],
    strip_prefix = "grpc-a2f731fc48581401776582489d80d4622c8aa536",
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
