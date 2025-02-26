#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <unordered_set>
#include <vector>

// Use a static flag to prevent recursive tracking
static bool tracking_enabled = true;

// Use unordered_set instead of vector for better performance
static std::unordered_set<void *> allocated_memory;

void *operator new(size_t size) {
  void *ptr = std::malloc(size);
  if (!ptr)
    throw std::bad_alloc();

  // Only track if we're not already tracking (prevents recursion)
  if (tracking_enabled) {
    tracking_enabled = false; // Temporarily disable tracking
    allocated_memory.insert(
        ptr);                // This might allocate memory, but won't be tracked
    tracking_enabled = true; // Re-enable tracking
  }
  return ptr;
}
bool isMemoryAllocated(void *ptr) {
  return allocated_memory.find(ptr) != allocated_memory.end();
}
void operator delete(void *ptr) noexcept {
  if (!ptr)
    return;

  if (tracking_enabled) {
    tracking_enabled = false; // Temporarily disable tracking
    allocated_memory.erase(ptr);
    tracking_enabled = true; // Re-enable tracking
  }
  std::free(ptr);
}
int main() {
  int *dynamicVar = new int(15);
  std::vector<std::vector<int>> s(3);
  std::fill(s.begin(), s.end(), std::vector<int>(10));

  std::cout << *dynamicVar << "\n";
  std::cout << "memory\n";
  for (const auto *ptr : allocated_memory) {
    std::cout << ptr << "\n";
  }
  std::cout << isMemoryAllocated(dynamicVar) << "\n";
  delete dynamicVar;
  std::cout << isMemoryAllocated(dynamicVar) << "\n";
  return 0;
}
