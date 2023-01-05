#include <gtest/gtest.h>

#include <di/Factory.hpp> 

#include "src/test/classes.hpp"

TEST(constructor_factory, construct_from_int) {
  std::unique_ptr<FactoryIntInterface> factory(new ConstructorFactoryIntD);
  std::unique_ptr<I> instance(factory->Create(1337));
  ASSERT_EQ(instance->Value(), 1337);
}

TEST(constructor_factory, construct_from_string) {
  std::unique_ptr<FactoryStringInterface> factory(new ConstructorFactoryStringD);
  std::unique_ptr<I> instance(factory->Create("abacaba"));
  ASSERT_EQ(instance->Value(), 7);
}

TEST(constructor_factory, construct_combined) {
  using MyFactory = di::CombinedFactory<ConstructorFactoryIntD, ConstructorFactoryStringD>;
  MyFactory factory;
  std::unique_ptr<I> int_instance(factory.Create(1337));
  std::unique_ptr<I> string_instance(factory.Create("abacaba"));
  ASSERT_EQ(int_instance->Value(), 1337);
  ASSERT_EQ(string_instance->Value(), 7);
}

