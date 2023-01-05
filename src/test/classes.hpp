#ifndef LIB_TEST_DI_CLASSES_HPP
#define LIB_TEST_DI_CLASSES_HPP

#include "src/test/proto/classes.pb.h"

#include <di/Factory.hpp>
#include <di/RuntimeSingleton.hpp>
#include <di/TagDispatcher.hpp>
#include <di/Dispatcher.hpp>

extern std::string i_json_config;

struct I {
  virtual ~I() = default;
  virtual int Value() = 0;
};

struct D : public I {
  explicit D(int x);
  explicit D(const std::string& s);
  explicit D(const DProto& proto);

  int Value() override;
  int x;
};

using FactoryIntInterface = di::Factory<I, int>;
using FactoryStringInterface = di::Factory<I, const std::string&>;
using ProtoFactoryInterface = di::Factory<I, const IProto&>;
using TagIntFactoryInterface = di::Factory<I, const std::string&, int>;

using ConstructorFactoryIntD = di::ConstructorFactory<FactoryIntInterface, D>;
using ConstructorFactoryStringD = di::ConstructorFactory<FactoryStringInterface, D>;

using TagIntDispatcher = di::NameDispatcher<I, int>;

using TagIntDispatcherRegisterD =
  TagIntDispatcher::Register<
    /* Implementation = */ D,
    /* ArgDispatcher = */ di::UndefinedArgDispatcher
  >;

using ProtoTagDispatcher =
  di::FieldTagDispatcher<
    /* ArgType = */ IProto,
    /* TagType = */ std::string,
    /* GetTag = */ &IProto::impl
  >;

using ProtoArgDispatcherD =
  di::FieldArgDispatcher<
    /* ArgType = */ IProto,
    /* ImplArg = */ DProto,
    /* Getter = */ &IProto::dproto
  >;

using ProtoDispatcher =
  di::Dispatcher<
    /* Interface = */ I,
    /* Tag = */ std::string,
    /* TagDispatcher = */ ProtoTagDispatcher,
    /* Args... = */ const IProto&
  >;

using ProtoDispatcherRegisterD =
  ProtoDispatcher::Register<
    /* Implementation = */ D,
    /* ArgDispatcher = */ ProtoArgDispatcherD
  >;

using SingletonInt = di::RuntimeSingleton<I, di::StrictThrow>;
using SingletonProto = di::RuntimeSingleton<I, di::StrictThrow, ProtoDispatcher>;

using DispatcherFactoryInt = di::DispatcherFactory<TagIntDispatcher>;
using DispatcherFactoryProto = di::DispatcherFactory<ProtoDispatcher>;

#endif  // LIB_TEST_DI_CLASSES_HPP

