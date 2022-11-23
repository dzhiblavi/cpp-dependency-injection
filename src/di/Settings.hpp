#ifndef LIB_DI_SETTINGS_HPP
#define LIB_DI_SETTINGS_HPP

#include <cassert>
#include <exception>
#include <stdexcept>

namespace di {

struct SettingsBase {};

template <bool Strict, bool EnableExceptions>
struct Settings : public SettingsBase {
  static constexpr bool strict = Strict;
  static constexpr bool enable_exceptions = EnableExceptions;

  [[noreturn]] static void FailWithMessage(const char* msg) noexcept(!enable_exceptions) {
    if constexpr(enable_exceptions) {
      throw std::runtime_error(msg);
    } else {
      assert(!static_cast<bool>(msg));
      std::terminate();
    }
    __builtin_unreachable();
  }
};

using LooseNothrow = Settings<false, false>;
using LooseThrow = Settings<false, true>;
using StrictNothrow = Settings<true, false>;
using StrictThrow = Settings<true, true>;

}  // namespace di

#endif  // LIB_DI_SETTINGS_HPP

