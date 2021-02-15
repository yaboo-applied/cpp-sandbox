load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_test(
    name = "turtle_test",
    srcs = [
        "turtle_test.cc",
        "mock_turtle.h",
    ],
    deps = [
        "@com_google_googletest//:gtest",
        "//turtle:painter"
    ],
)

cc_library(
    name = "painter",
    srcs = [
        "painter.cc",
        "painter.h",
        "turtle.h",
    ]
)
