#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  std::string a{"AAAA"};
  std::string &&b{std::move(a)};

  std::cout << "A: " << a << "\n";
  std::cout << "B: " << b << "\n";
  return 0;
}
