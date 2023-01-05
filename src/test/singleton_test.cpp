#include <gtest/gtest.h>
#include <google/protobuf/util/json_util.h>

#include "src/test/classes.hpp"

using PSingleton = di::RuntimeSingleton<I, di::StrictThrow>;
using ASingleton = di::RuntimeSingleton<I, di::LooseThrow>;

TEST(singleton, reinject_prohibited) {

  ASSERT_FALSE(PSingleton::Injected());
  PSingleton::Inject(new D(1));
  ASSERT_TRUE(PSingleton::Injected());
  EXPECT_EQ(1, PSingleton::Get().Value());
  ASSERT_THROW(PSingleton::Inject(new D(2)), std::runtime_error);
  PSingleton::Discard();
  ASSERT_FALSE(PSingleton::Injected());
  PSingleton::Inject(new D(2));
  ASSERT_TRUE(PSingleton::Injected());
  EXPECT_EQ(2, PSingleton::Get().Value());
}

TEST(singleton, reinject_allowed) {
  ASSERT_FALSE(ASingleton::Injected());
  ASingleton::Inject(new D(1));
  ASSERT_TRUE(ASingleton::Injected());
  EXPECT_EQ(1, ASingleton::Get().Value());
  ASingleton::Inject(new D(2));
  ASSERT_TRUE(ASingleton::Injected());
  EXPECT_EQ(2, ASingleton::Get().Value());
}


TEST(protobuf_singleton, impl_test) {
  IProto iproto;
  google::protobuf::util::JsonStringToMessage(i_json_config, &iproto);
  using SingletonProto = di::RuntimeSingleton<I, di::StrictThrow, ProtoDispatcher>;
  SingletonProto::Inject(iproto);
  I& i = SingletonProto::Get();
  EXPECT_EQ(iproto.dproto().x(), i.Value());
}

