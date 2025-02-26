#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  std::string a{"AAAA"};
  std::string &b{a};
  std::string &&c{std::move("assa")};
  c = "JJAKL";
  std::cout << "A: " << a << "\n";
  std::cout << "B: " << b << "\n";
  std::cout << "C: " << c << "\n";
  return 0;
}
