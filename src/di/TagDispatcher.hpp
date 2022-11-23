#ifndef LIB_DI_TAG_DISPATCHER_HPP
#define LIB_DI_TAG_DISPATCHER_HPP

#include <concepts>
#include <string>

namespace di {

struct TagDispatcherBase {};

template <typename T>
concept IsTagDispatcher = std::derived_from<T, TagDispatcherBase>;

struct UndefinedTagDispatcher : public TagDispatcherBase {};

template <typename ArgType, typename TagType, const TagType& (ArgType::*Getter)() const>
struct FieldTagDispatcher : public TagDispatcherBase {
  static const TagType& DispatchTag(const ArgType& arg) { return (arg.*Getter)(); }
};

struct ArgDispatcherBase {};

template <typename T>
concept IsArgDispatcher = std::derived_from<T, ArgDispatcherBase>;

struct UndefinedArgDispatcher : public ArgDispatcherBase {};

template <typename ArgType, typename ImplArg, const ImplArg& (ArgType::*Getter)() const>
struct FieldArgDispatcher : public ArgDispatcherBase {
  static const ImplArg& DispatchArg(const ArgType& arg) { return (arg.*Getter)(); }
};

};

#endif  // LIB_DI_TAG_DISPATCHER_HPP
