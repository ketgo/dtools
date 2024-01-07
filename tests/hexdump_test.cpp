// Copyright (c) 2024 Ketan Goyal
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <gtest/gtest.h>

#include <fstream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include <dtools/hexdump.hpp>

namespace {

constexpr auto kBufferSize = 1024;
constexpr auto kExpectedDumpFilePath = "tests/hexdump_test.data";

}  // namespace

TEST(HexDumpTestFixture, TestDumping) {
  std::vector<uint8_t> buffer(kBufferSize);
  const size_t max_value = std::numeric_limits<uint8_t>::max() + 1;
  for (size_t i = 0; i < buffer.size(); ++i) {
    buffer[i] = i % max_value;
  }

  // Loading expected dump from file
  std::ifstream file(kExpectedDumpFilePath);
  std::string line, expected_dump;
  while (std::getline(file, line)) {
    expected_dump += line;
    expected_dump.push_back('\n');
  }
  const std::string address = "0x7fd502008200";
  std::stringstream expected_address;
  expected_address << static_cast<const void*>(buffer.data());
  expected_dump.replace(expected_dump.find(address), address.size(),
                        expected_address.str());

  // Dumping
  std::stringstream dump;
  dump << dtools::HexDump(buffer.data(), buffer.size());

  ASSERT_EQ(dump.str(), expected_dump);
}
