# Copyright (c) 2024 Ketan Goyal
#
# This software is released under the MIT License.
# https://opensource.org/licenses/MIT

workspace(name = "dtools")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# --------------------------------------
# Gtest
# --------------------------------------

http_archive(
    name = "com_google_absl",
    sha256 = "6764f226bd6e2d8ab9fe2f3cab5f45fb1a4a15c04b58b87ba7fa87456054f98b",
    strip_prefix = "abseil-cpp-273292d1cfc0a94a65082ee350509af1d113344d",
    urls = ["https://github.com/abseil/abseil-cpp/archive/273292d1cfc0a94a65082ee350509af1d113344d.zip"],
)

http_archive(
    name = "gtest",
    sha256 = "ab78fa3f912d44d38b785ec011a25f26512aaedc5291f51f3807c592b506d33a",
    strip_prefix = "googletest-58d77fa8070e8cec2dc1ed015d66b454c8d78850",
    urls = ["https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip"],
)
