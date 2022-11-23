#include "src/test/classes.hpp"

D::D(int x) : x(x) {}

D::D(const DProto& proto) : x(proto.x()) {}

int D::Value() { return x; }

[[maybe_unused]] RegisterD r("D");

std::string i_json_config =
  "{                  "
  "  \"impl\": \"D\", "
  "  \"dproto\": {    "
  "     \"x\": 239    "
  "  }                "
  "}                  ";

