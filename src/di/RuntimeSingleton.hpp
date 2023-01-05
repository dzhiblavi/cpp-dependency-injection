#ifndef LIB_DI_RUNTIME_SINGLETON_HPP
#define LIB_DI_RUNTIME_SINGLETON_HPP

#include <concepts>
#include <type_traits>
#include <memory>

#include "src/di/Settings.hpp"

namespace di {

template <
  typename Interface,
  std::derived_from<SettingsBase> Settings,
  typename Dispatcher = void>
class RuntimeSingleton {
 public:
  ~RuntimeSingleton() noexcept { Discard(); }

  static Interface& Get() noexcept(!Settings::enable_exceptions) {
    if (instance_ == nullptr) {
      Settings::FailWithMessage("SingletonInterface: instance not registered");
    }
    return *instance_;
  }

  template <std::derived_from<Interface> T>
  static void Inject(T* object) noexcept(!Settings::enable_exceptions) {
    CheckAndDiscard();
    instance_ = object;
  }

  template <typename... Args>
  static void Inject(Args&&... args) {
    std::unique_ptr<Interface> uptr(Dispatcher::Create(std::forward<Args>(args)...));
    Inject(uptr.get());
    uptr.release();
  }

  static void Discard() noexcept {
    if (instance_ != nullptr) {
      delete instance_;
      instance_ = nullptr;
    }
  }

  static bool Injected() noexcept { return instance_ != nullptr; }

 private:
  static void CheckAndDiscard() noexcept(!Settings::enable_exceptions) {
    if (instance_ != nullptr) {
      if constexpr(Settings::strict) {
        Settings::FailWithMessage("SingletonInterface: reinjection not allowed");
      } else {
        Discard();
      }
    }
  }

  static Interface* instance_;
};

template <typename Interface, std::derived_from<SettingsBase> Settings, typename Dispatcher>
Interface* RuntimeSingleton<Interface, Settings, Dispatcher>::instance_ = nullptr;

}  // namespace di

#endif  // LIB_DI_RUNTIME_SINGLETON_HPP

