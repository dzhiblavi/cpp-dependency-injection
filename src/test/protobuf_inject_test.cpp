#include <gtest/gtest.h>
#include <google/protobuf/util/json_util.h>

#include "src/test/classes.hpp"

TEST(protobuf_inject, factory_test) {
  IProto iproto;
  google::protobuf::util::JsonStringToMessage(i_json_config, &iproto);

  std::unique_ptr<IFactoryProto> d(new IFactoryProtoImpl());
  std::unique_ptr<I> i(d->Create(iproto));
  //EXPECT_EQ(iproto.dproto().x(), i->Value());
}

