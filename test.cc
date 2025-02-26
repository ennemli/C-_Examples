#include <string>
struct InnerStruct {
  int x;
  std::string name;
};

struct OuterStruct {
  InnerStruct inner{};
  int value;
};

// Let's examine different scenarios
void example() {

  // OuterStruct().inner = InnerStruct{}; // Error
  // OuterStruct().inner.x = 5;           // Error
  // OuterStruct().value = 10;            // Error
  int x = 2, b = 3;
  (x == b ? 4 : 5) = true;
}
