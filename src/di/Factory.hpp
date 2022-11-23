#ifndef LIB_DI_FACTORY_HPP
#define LIB_DI_FACTORY_HPP

#include <concepts>
#include <utility>

namespace di {

template <typename Interface, typename... Args>
class Factory {
 public:
  virtual ~Factory() = default;
  [[nodiscard]] virtual Interface* Create(Args... args) = 0;
};

template <typename FactoryBase, typename Implementation>
class ConstructorFactory;

template <typename Interface, typename Implementation, typename... Args>
  requires std::constructible_from<Implementation, Args...>
class ConstructorFactory<Factory<Interface, Args...>, Implementation>
  : public Factory<Interface, Args...> {
 public:
  [[nodiscard]] Interface* Create(Args... args) override {
    return new Implementation(std::forward<Args>(args)...);
  }
};

template <typename FactoryBase, typename Dispatcher>
class DispatcherFactory;

template <typename Interface, typename Dispatcher, typename... Args>
class DispatcherFactory<Factory<Interface, Args...>, Dispatcher>
  : public Factory<Interface, Args...> {
 public:
  [[nodiscard]] Interface* Create(Args... args) override {
    return Dispatcher::Create(std::forward<Args>(args)...);
  }
};

}  // namespace di

#endif  // LIB_DI_FACTORY_HPP

