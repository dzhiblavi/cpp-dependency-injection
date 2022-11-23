package(default_visibility = ["//visibility:public"])

load("@rules_cc//cc:defs.bzl", "cc_library")
load("@rules_proto//proto:defs.bzl", "proto_library")

cc_proto_library(
    name = "classes_cc_proto",
    deps = [":classes_proto"],
)

proto_library(
    name = "classes_proto",
    srcs = ["classes.proto"],
    deps = [
        "@com_google_protobuf//:any_proto",
    ],
)

