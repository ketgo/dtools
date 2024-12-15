
#include <dtools/dprint.hpp>

namespace dtools {
namespace internal {

std::ostream*& getStream() {
  static std::ostream* out = std::addressof(std::cout);
  return out;
}

ScopedStream::ScopedStream(std::mutex& mutex, std::ostream& out)
    : lock_(mutex), out_(out) {
  out_ << std::chrono::system_clock::now().time_since_epoch().count() << "\t"
       << std::this_thread::get_id() << "\t~\t";
}

// static
ScopedStream ScopedStream::create(std::ostream& out) {
  static std::mutex mutex;
  return {mutex, out};
}

ScopedStream::~ScopedStream() { out_ << "\n"; }

}  // namespace internal

void setStream(std::ostream& out) {
  internal::getStream() = std::addressof(out);
}

void resetStream() { setStream(std::cout); }

}  // namespace dtools