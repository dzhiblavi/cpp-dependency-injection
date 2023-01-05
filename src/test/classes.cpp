#include "src/test/classes.hpp"

D::D(int x) : x(x) {}

D::D(const std::string& x) : x(x.size()) {}

D::D(const DProto& proto) : x(proto.x()) {}

int D::Value() { return x; }

std::string i_json_config =
  "{                  "
  "  \"impl\": \"D\", "
  "  \"dproto\": {    "
  "     \"x\": 239    "
  "  }                "
  "}                  ";

[[maybe_unused]] ProtoDispatcherRegisterD D_reg_proto("D");
[[maybe_unused]] TagIntDispatcherRegisterD D_reg_tag_int("D");

