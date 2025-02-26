#include <cstring>
#include <iostream>
#include <string>

using namespace std;
int main(int argc, char *argv[]) {
  char buffer[] = "Hello, World!";

  // Overlapping memory regions: copying within the same buffer
  memmove(buffer + 3, buffer, 5);
  cout << buffer << '\n';
  return 0;
}
