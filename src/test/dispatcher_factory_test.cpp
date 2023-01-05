#include <gtest/gtest.h>
#include <google/protobuf/util/json_util.h>

#include <di/Factory.hpp> 

#include "di/Dispatcher.hpp"
#include "src/test/classes.hpp"

TEST(dispatcher_factory, dispatch_by_explicit_tag) {
  std::unique_ptr<TagIntFactoryInterface> factory(new DispatcherFactoryInt);
  std::unique_ptr<I> instance(factory->Create("D", 1337));
  ASSERT_EQ(instance->Value(), 1337);
}

TEST(dispatcher_factory, dispatch_by_protobuf_field) {
  IProto iproto;
  google::protobuf::util::JsonStringToMessage(i_json_config, &iproto);

  std::unique_ptr<ProtoFactoryInterface> factory(new DispatcherFactoryProto);
  std::unique_ptr<I> instance(factory->Create(iproto));
  ASSERT_EQ(instance->Value(), 239);
}

TEST(dispatcher_factory, construct_combined) {
  IProto iproto;
  google::protobuf::util::JsonStringToMessage(i_json_config, &iproto);

  using MyFactory = di::CombinedFactory<DispatcherFactoryInt, DispatcherFactoryProto>;
  MyFactory factory;

  std::unique_ptr<I> tag_instance(factory.Create("D", 1337));
  std::unique_ptr<I> proto_instance(factory.Create(iproto));
  ASSERT_EQ(tag_instance->Value(), 1337);
  ASSERT_EQ(proto_instance->Value(), 239);
}

