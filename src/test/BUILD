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
        "combined_factory_test.cpp",
        "constructor_factory_test.cpp",
        "dispatcher_factory_test.cpp",
        "singleton_test.cpp",
    ],
    deps = [
        ":di_test_lib",
        "@com_google_googletest//:gtest",
        "@com_google_googletest//:gtest_main",
    ],
)

