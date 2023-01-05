load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

http_archive(
    name = "com_google_googletest",
    urls = ["https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip"],
    strip_prefix = "googletest-release-1.12.1",
)

http_archive(
    name = "rules_foreign_cc",
    sha256 = "040ad10c9f760babdd0ade6746881f76d150e75838a2833342d1f7e245bcec42",
    strip_prefix = "rules_foreign_cc-e97f24e701cc33c0e4aa360d59b83eca0aa46111",
    url = "https://github.com/bazelbuild/rules_foreign_cc/archive/e97f24e701cc33c0e4aa360d59b83eca0aa46111.tar.gz",
)
load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")
rules_foreign_cc_dependencies()

http_archive(
    name = "rules_cc",
    urls = ["https://github.com/bazelbuild/rules_cc/releases/download/0.0.1/rules_cc-0.0.1.tar.gz"],
    sha256 = "4dccbfd22c0def164c8f47458bd50e0c7148f3d92002cdb459c2a96a68498241",
)
load("@rules_cc//cc:repositories.bzl", "rules_cc_dependencies")
rules_cc_dependencies()

git_repository(
    name = "rules_proto",
    shallow_since = "1610710171 +0100",
    commit = "cfdc2fa31879c0aebe31ce7702b1a9c8a4be02d2",
    remote = "https://github.com/bazelbuild/rules_proto.git",
)
load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")
rules_proto_toolchains()
rules_proto_dependencies()

load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")
protobuf_deps()

