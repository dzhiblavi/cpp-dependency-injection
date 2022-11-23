cc_library(
    name = "di_test_lib",
    hdrs = [
        "classes.hpp",
    ],
    srcs = [
        "classes.cpp",
    ],
    deps = [
        "//src/di",
        "//src/test/proto:classes_cc_proto",
    ],
)

cc_test(
    name = "di_test",
    srcs = [
        "all_factories_test.cpp",
        "protobuf_inject_test.cpp",
        "protobuf_singleton_test.cpp",
        "inject_test.cpp",
        "runtime_singleton_test.cpp",
    ],
    deps = [
        ":di_test_lib",
        "@com_google_googletest//:gtest",
        "@com_google_googletest//:gtest_main",
    ],
)

