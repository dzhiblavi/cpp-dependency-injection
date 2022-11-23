#include <gtest/gtest.h>

#include <di/RuntimeSingleton.hpp> 

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

