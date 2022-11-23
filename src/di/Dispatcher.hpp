#ifndef LIB_DI_DISPATCHER_HPP
#define LIB_DI_DISPATCHER_HPP

#include <tuple>
#include <string>
#include <unordered_map>

#include "src/di/detail.hpp"
#include "src/di/TagDispatcher.hpp"

namespace di {

template <typename Implementation, typename... Args>
using DefaultBuilder = decltype(+[] (Args&&... args) {
  return new Implementation(std::forward<Args>(args)...);
});

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
      if constexpr(std::same_as<ArgDispatcher, UndefinedArgDispatcher>) {
        using DefaultBuilderType = DefaultBuilder<Implementation, Args...>;
        RegisterImpl(tag, DefaultBuilderType()); 
      } else {
        using Arg = detail_::nth_type_t<0, ArgsTuple>;
        RegisterImpl(tag, +[](const Arg& arg) -> TInterface* {
          return new Implementation(ArgDispatcher::DispatchArg(arg));
        });
      }
    }

   private:
    void RegisterImpl(const Tag& tag, Builder&& builder) { AddBuilder(tag, std::move(builder)); }
  };

  static void AddBuilder(const Tag& tag, Builder builder) {
    builders_.emplace(tag, std::move(builder));
  }

  [[nodiscard]] static Interface* Create(const Tag& tag, Args... args) {
    return CreateImpl(tag, std::forward<Args>(args)...);
  }

  [[nodiscard]] static Interface* Create(Args... args) {
    const Tag& tag = TagDispatcher::DispatchTag(args...);
    return CreateImpl(tag, std::forward<Args>(args)...);
  }

 private:
  Dispatcher() = delete;

  [[nodiscard]] static Interface* CreateImpl(const Tag& tag, Args... args) {
    return builders_.at(tag)(std::forward<Args>(args)...);
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
