#include <memory>
class A {
private:
  static int x;
};
int A::x = 9;

struct Point {
  struct Coord { // object type
    int x, y;
  };
  Coord coord;
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  Point p;
  std::move(p).coord

      return 0;
}
