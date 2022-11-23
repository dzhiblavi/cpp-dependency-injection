#ifndef LIB_DI_GETTER_HPP
#define LIB_DI_GETTER_HPP

#define getter(type, method) [](type t) -> decltype(auto) { return t.method(); }

#define getter_t(type, method) decltype(getter(type, method))

#endif  // LIB_DI_GETTER_HPP
