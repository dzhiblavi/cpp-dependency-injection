#ifndef LIB_DI_FACTORY_HPP
#define LIB_DI_FACTORY_HPP

#include <concepts>
#include <utility>

#include "src/di/Dispatcher.hpp"

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

template <typename Dispatcher>
class DispatcherFactory;

template <typename Interface, typename Tag, IsTagDispatcher TagDispatcher, typename... Args>
class DispatcherFactory<Dispatcher<Interface, Tag, TagDispatcher, Args...>>
  : public Factory<Interface, Args...> {
 public:
  using DispatcherType = Dispatcher<Interface, Tag, TagDispatcher, Args...>;

  [[nodiscard]] Interface* Create(Args... args) {
    return DispatcherType::Create(std::forward<Args>(args)...);
  }
};

template <typename Interface, typename Tag, typename... Args>
class DispatcherFactory<Dispatcher<Interface, Tag, UndefinedTagDispatcher, Args...>>
  : public Factory<Interface, const Tag&, Args...> {
 public:
  using DispatcherType = Dispatcher<Interface, Tag, UndefinedTagDispatcher, Args...>;

  [[nodiscard]] Interface* Create(const Tag& tag, Args... args) {
    return DispatcherType::Create(tag, std::forward<Args>(args)...);
  }
};

template <typename... Factories>
struct CombinedFactory : public Factories... { using Factories::Create...; };

}  // namespace di

#endif  // LIB_DI_FACTORY_HPP

