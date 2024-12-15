// Copyright (c) 2024 Ketan Goyal
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

#include <iostream>
#include <mutex>
#include <thread>

namespace dtools {
namespace internal {

/**
 * @brief Get the output stream of the DPRINT lib.
 *
 * @returns Pointer to the output stream.
 */
std::ostream*& getStream();

/**
 * @brief The class `ScopedStream` streams given input to an output stream
 * scoped by a mutex.
 *
 */
class ScopedStream {
 public:
  /**
   * @brief Create a scoped stream object.
   *
   * @param out Reference to output stream.
   */
  static ScopedStream create(std::ostream& out = *internal::getStream());

  /**
   * @brief Print the given input to standard output.
   *
   * @tparam T The type of trace event.
   * @param event Constant reference to the event.
   * @returns Reference to the scoped trace.
   */
  template <class T>
  ScopedStream& operator<<(const T& event);

  /**
   * @brief Destroy the Scoped Trace object
   *
   */
  ~ScopedStream();

 private:
  /**
   * @brief Construct a new ScopedTrace object.
   *
   * @param mutex Reference to the mutex.
   * @param out Reference to output stream.
   */
  ScopedStream(std::mutex& mutex, std::ostream& out);

  std::unique_lock<std::mutex> lock_;
  std::ostream& out_;
};

// ------------------------------------
// ScopedStream Implementation
// ------------------------------------

template <class T>
ScopedStream& ScopedStream::operator<<(const T& event) {
  out_ << event;
  return *this;
}

// ------------------------------------

}  // namespace internal

/**
 * @brief Set the output stream of the DPRINT lib.
 *
 * @param out Reference to the output stream.
 */
void setStream(std::ostream& out);

/**
 * @brief Rest the output stream of the DPRINT lib to the default stream, i.e.
 * stdout.
 *
 */
void resetStream();

}  // namespace dtools

/**
 * @brief Macro for debug print to stdout.
 *
 */
#define DPRINT dtools::internal::ScopedStream::create()

/**
 * @brief Macro for debug print to given stream.
 *
 */
#define DPRINT_TO(stream) dtools::internal::ScopedStream::create(stream)