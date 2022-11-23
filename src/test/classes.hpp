#ifndef LIB_TEST_DI_CLASSES_HPP
#define LIB_TEST_DI_CLASSES_HPP

#include "src/test/proto/classes.pb.h"

#include <di/Factory.hpp>
#include <di/RuntimeSingleton.hpp>
#include <di/TagDispatcher.hpp>
#include <di/Dispatcher.hpp>
#include <di/getter.hpp>

extern std::string i_json_config;

struct I {
  virtual ~I() = default;
  virtual int Value() = 0;
};

struct D : public I {
  explicit D(int x);
  explicit D(const DProto& proto);
  int Value() override;
  int x;
};

using Singleton =
  di::RuntimeSingleton<
    /* Interface = */ I,
    /* Settings = */ di::StrictThrow
  >;

using ProtoTagDispatcher = di::FieldTagDispatcher<
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
    /* Args... = */ const IProto&>;

using RegisterD =
  ProtoDispatcher::Register<
    /* Implementation = */ D,
    /* ArgDispatcher = */ ProtoArgDispatcherD
  >;

using IFactoryInt = di::Factory<I, int>;
using IFactoryIntConstr = di::ConstructorFactory<IFactoryInt, D>;
using IFactoryIntDispatch = di::DispatcherFactory<IFactoryInt, di::NameDispatcher<I, int>>;

using IFactoryProto = di::Factory<I, const IProto&>;
using IFactoryProtoImpl = di::DispatcherFactory<IFactoryProto, ProtoDispatcher>;

using ISingletonInt = di::RuntimeSingleton<I, di::StrictThrow>;
using ISingletonProto = di::RuntimeSingleton<I, di::StrictThrow, ProtoDispatcher>;

//struct IFactory : public IFactoryIntImpl, public IFactoryProtoImpl {
  //using IFactoryIntImpl::Create;
  //using IFactoryProtoImpl::Create;
//};

#endif  // LIB_TEST_DI_CLASSES_HPP

