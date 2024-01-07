// Copyright (c) 2024 Ketan Goyal
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

#include <cctype>
#include <ostream>

namespace dtools {

/**
 * @brief Print content at the given memory location and of given size in hex
 * notation.
 *
 */
class HexDump {
 public:
  /**
   * @brief Data structure containing formatting to be used when dumping.
   *
   */
  struct Format {
    // Number of 8-bit hex values to print per row.
    size_t row_size;
    // Right align value. This is the number of spaces to leave before starting
    // to dump.
    size_t right_align;
    // Number of spaces to leave between borders and hex dump body.
    size_t margin_size;
  };

  /**
   * @brief Get the default format to be used for dumping.
   *
   */
  static constexpr Format defaultFormat() { return {16, 4, 1}; }

  /**
   * @brief Construct a new HexDump object.
   *
   * @param data Constant pointer to the start of the memory region to dump.
   * @param size Size of the memory region to dump.
   * @param format Constant reference to the formatting information.
   */
  HexDump(const void *data, const size_t size,
          const Format &format = defaultFormat());

  /**
   * @brief Method to write the HexDump object to the given output stream.
   *
   * @param out Reference to the output stream.
   * @param dump Constant reference to a HexDump object.
   * @returns Reference to the given output stream.
   */
  friend std::ostream &operator<<(std::ostream &out, const HexDump &dump);

 private:
  const unsigned char *data_;
  const size_t size_;
  const Format format_;
};

}  // namespace dtools