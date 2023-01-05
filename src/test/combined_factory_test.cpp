#include <gtest/gtest.h>
#include <google/protobuf/util/json_util.h>

#include <di/Factory.hpp> 

#include "di/Dispatcher.hpp"
#include "src/test/classes.hpp"

using CombinedFactory =
  di::CombinedFactory<
    ConstructorFactoryIntD,
    ConstructorFactoryStringD,
    DispatcherFactoryInt,
    DispatcherFactoryProto
  >;

TEST(combined_factory, many_factories_combined) {
  IProto iproto;
  google::protobuf::util::JsonStringToMessage(i_json_config, &iproto);

  CombinedFactory factory;
  std::unique_ptr<I> int_instance(factory.Create(17));
  std::unique_ptr<I> string_instance(factory.Create("abacaba"));
  std::unique_ptr<I> tag_int_instance(factory.Create("D", 1337));
  std::unique_ptr<I> proto_instance(factory.Create(iproto));

  ASSERT_EQ(int_instance->Value(), 17);
  ASSERT_EQ(string_instance->Value(), 7);
  ASSERT_EQ(tag_int_instance->Value(), 1337);
  ASSERT_EQ(proto_instance->Value(), 239);
}

