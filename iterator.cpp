#include <iostream>
#include <iterator>

int main() {
  std::cout << "Enter some numbers (end with Ctrl+D or Ctrl+Z):\n";

  // Single-pass iterator: std::istream_iterator
  std::istream_iterator<int> it(std::cin), end;

  // First pass: Reading the input
  std::cout << "First pass: ";
  while (it != end) {
    std::cout << *it << " "; // Read and print
    ++it;                    // Advance the iterator
  }
  std::cout << "\n";

  // Reset the iterator for a second pass (NOT POSSIBLE with istream_iterator)
  it = std::istream_iterator<int>(std::cin);

  // Second pass: Trying to re-read the input (will not work)
  std::cout << "Second pass: ";
  while (it != end) {
    std::cout << *it
              << " "; // This will NOT work as the stream is already consumed
    ++it;
  }
  std::cout << "\n";

  return 0;
}
