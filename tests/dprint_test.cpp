// Copyright (c) 2024 Ketan Goyal
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <gtest/gtest.h>

#include <dtools/dprint.hpp>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

std::vector<std::string> split(const std::string& string,
                               const std::string& delimeter) {
  std::vector<std::string> splits;
  std::size_t pos_start = 0, pos_end = 0;

  while ((pos_end = string.find(delimeter, pos_start)) != std::string::npos) {
    std::string token = string.substr(pos_start, pos_end - pos_start);
    splits.push_back(token);
    pos_start = pos_end + delimeter.length();
  }
  std::string token = string.substr(pos_start);
  splits.push_back(token);

  return splits;
}

TEST(DPrintTestFixture, TestPrint) {
  constexpr auto kThreadCount = 10;

  std::stringstream out;
  std::vector<std::thread> threads(kThreadCount);

  dtools::setStream(out);

  for (auto& thread : threads) {
    thread = std::thread([&]() { DPRINT << "Testing"; });
  }

  for (auto& thread : threads) {
    if (thread.joinable()) {
      thread.join();
    }
  }

  const auto data = out.str();
  const auto lines = split(data, "\n");
  // We add 1 to account for last line delimiter
  ASSERT_EQ(lines.size(), kThreadCount + 1);
}