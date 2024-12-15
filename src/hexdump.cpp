// Copyright (c) 2024 Ketan Goyal
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <dtools/hexdump.hpp>

#include <iomanip>
#include <string>

namespace dtools {

namespace {

/**
 * @brief Width used to print address
 *
 */
constexpr auto kAddressWidth = 14;

/**
 * @brief Width used to print address offsets
 *
 */
constexpr auto kAddressOffsetWidth = 6;

/**
 * @brief Width used to print 8-bit hex values.
 *
 */
constexpr auto kHexWidth = 2;

/**
 * @brief Char to use for printing vertical border.
 *
 */
constexpr char kVerticalBorder = '|';

/**
 * @brief Char to use for printing horizontal border.
 *
 */
constexpr char kHorizontalBorder = '-';

}  // namespace

HexDump::HexDump(const void *data, const size_t size, const Format &format)
    : data_(static_cast<const unsigned char *>(data)),
      size_(size),
      format_(format) {}

std::ostream &operator<<(std::ostream &out, const HexDump &dump) {
  // Saving state of stream
  std::ios state(nullptr);
  state.copyfmt(out);

  const auto page_width =
      2 * (1 + dump.format_.margin_size)         // Margins and borders
      + (kAddressOffsetWidth + 4)                // Address offset
      + (kHexWidth + 1) * dump.format_.row_size  // Hex dump
      + 1                                        // Hex and ascii dump separate
      + dump.format_.row_size;                   // Ascii dump
  const auto right_align = std::string(dump.format_.right_align, ' ');
  const auto margin = std::string(dump.format_.margin_size, ' ');
  const auto pre_fill = right_align + kVerticalBorder + margin;
  const auto post_fill = margin + kVerticalBorder;

  // Printing header
  out.fill(kHorizontalBorder);
  out << right_align << "+" << std::setw(page_width - 1) << "+"
      << "\n";
  out.fill(' ');
  out << pre_fill << "ADDRESS: " << std::setw(kAddressWidth)
      << static_cast<const void *>(dump.data_)
      << std::setw(page_width - post_fill.size() - kAddressWidth - 9)
      << post_fill << "\n";
  out.fill(kHorizontalBorder);
  out << right_align << "+" << std::setw(page_width - 1) << "+"
      << "\n";

  // Printing body
  out.fill('0');
  for (size_t i = 0; i < dump.size_; i += dump.format_.row_size) {
    out << pre_fill;

    // Display memory address offset for the line
    out << "0x" << std::setw(kAddressOffsetWidth) << std::hex << i << ": ";

    // Display the content as hex for the line
    for (size_t j = 0; j < dump.format_.row_size; ++j) {
      if (i + j < dump.size_) {
        out << std::hex << std::setw(kHexWidth)
            << static_cast<int>(dump.data_[i + j]) << " ";
      } else {
        out << "   ";
      }
    }

    // Display the content as ASCII for the line
    out << " ";
    for (size_t j = 0; j < dump.format_.row_size; ++j) {
      if (i + j < dump.size_) {
        if (std::isprint(dump.data_[i + j])) {
          out << static_cast<char>(dump.data_[i + j]);
        } else {
          out << ".";
        }
      }
    }

    out << post_fill << "\n";
  }

  // Printing footer
  out << right_align << "+";
  out.fill(kHorizontalBorder);
  out << std::setw(page_width - 2) << ' ' << "+\n";

  // Restoring state of stream
  out.copyfmt(state);
  out << std::flush;

  return out;
}

}  // namespace dtools