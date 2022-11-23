#include <gtest/gtest.h>
#include <google/protobuf/util/json_util.h>

#include "src/test/classes.hpp"

TEST(protobuf_singleton, impl_test) {
  IProto iproto;
  google::protobuf::util::JsonStringToMessage(i_json_config, &iproto);

  ISingletonProto::Inject(iproto);
  I& i = ISingletonProto::Get();
  EXPECT_EQ(iproto.dproto().x(), i.Value());
}
