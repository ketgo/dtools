# Copyright (c) 2024 Ketan Goyal
#
# This software is released under the MIT License.
# https://opensource.org/licenses/MIT

cc_library(
    name = "hexdump",
    srcs = [
        "src/hexdump.cpp",
    ],
    hdrs = [
        "include/dtools/hexdump.hpp",
    ],
    includes = [
        "include",
    ],
    visibility = ["//visibility:public"],
    deps = [],
)

cc_library(
    name = "dtools",
    visibility = ["//visibility:public"],
    deps = [
        ":hexdump",
    ],
)
