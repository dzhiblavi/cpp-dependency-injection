#ifndef LIB_DI_DISPATCHER_HPP
#define LIB_DI_DISPATCHER_HPP

#include <tuple>
#include <string>
#include <unordered_map>
#include <iostream>
#include <cassert>

#include "src/di/TagDispatcher.hpp"

namespace di {

template <typename Interface, typename... Args>
using BuilderType = Interface* (*)(Args... args);

template <typename TInterface, typename Tag, IsTagDispatcher TagDispatcher, typename... Args>
class Dispatcher {
 public:
  using Interface = TInterface;
  using ArgsTuple = std::tuple<Args...>;
  using Builder = BuilderType<Interface, Args...>;

  template <typename Implementation, IsArgDispatcher ArgDispatcher>
  class Register {
   public:
    explicit Register(const Tag& tag) {
      if constexpr (std::same_as<ArgDispatcher, UndefinedArgDispatcher>) {
        RegisterImpl(tag, +[](Args... args) -> TInterface* { return new Implementation(args...); }); 
      } else {
        RegisterImpl(tag, +[](Args... args) -> TInterface* {
          return new Implementation(ArgDispatcher::DispatchArg(args...));
        });
      }
    }

   private:
    void RegisterImpl(const Tag& tag, Builder&& builder) { AddBuilder(tag, std::move(builder)); }
  };

  static void AddBuilder(const Tag& tag, Builder&& builder) {
    bool inserted = builders_.emplace(tag, std::move(builder)).second;
    assert(inserted);
  }

  [[nodiscard]] static Interface* Create(const Tag& tag, Args... args) {
    return CreateImpl(tag, std::forward<Args>(args)...);
  }

  [[nodiscard]] static Interface* Create(Args... args) {
    return CreateImpl(TagDispatcher::DispatchTag(args...), args...);
  }

 private:
  Dispatcher() = delete;

  [[nodiscard]] static Interface* CreateImpl(const Tag& tag, Args... args) {
    auto it = builders_.find(tag);
    assert(it != builders_.end());
    return it->second(std::forward<Args>(args)...);
  }

  static std::unordered_map<Tag, Builder> builders_;
};

template <typename TInterface, typename Tag, IsTagDispatcher TagDispatcher, typename... Args>
std::unordered_map<Tag, BuilderType<TInterface, Args...>>
Dispatcher<TInterface, Tag, TagDispatcher, Args...>::builders_;

template <typename Interface, typename... Args>
using NameDispatcher = Dispatcher<Interface, std::string, UndefinedTagDispatcher, Args...>;

}  // namespace di

#endif  // LIB_DI_DISPATCHER_HPP
