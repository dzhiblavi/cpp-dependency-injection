#include <gtest/gtest.h>

#include <di/Factory.hpp> 
#include <di/RuntimeSingleton.hpp> 

#include "src/test/classes.hpp"

TEST(inject, runtime_singleton) {
  Singleton::Inject(new D(2));

  I& i = Singleton::Get();
  EXPECT_EQ(2, i.Value());
  Singleton::Discard();
}

TEST(inject, runtime_factory) {
  std::unique_ptr<IFactoryInt> factory(new di::ConstructorFactory<IFactoryInt, D>());

  std::unique_ptr<I> i(factory->Create(5));
  EXPECT_EQ(5, i->Value());
}

