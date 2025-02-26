#include <iostream>
#include <mutex>
#include <stdexcept>

class Singleton {
public:
  // Accessor for the Singleton instance
  static Singleton &getInstance() {
    if (!instance_) {
      throw std::runtime_error(
          "Singleton not initialized. Call initialize() first.");
    }
    return *instance_;
  }

  // Initialization method
  static void initialize(int value, const std::string &name) {
    static std::once_flag initFlag;
    std::call_once(initFlag, [&]() { instance_ = new Singleton(value, name); });
  }

  // Delete copy constructor and assignment operator
  Singleton(const Singleton &) = delete;
  Singleton &operator=(const Singleton &) = delete;

  // Example method
  void display() const {
    std::cout << "Singleton: value = " << value_ << ", name = " << name_
              << '\n';
  }

private:
  // Private constructor to enforce Singleton
  Singleton(int value, const std::string &name) : value_(value), name_(name) {
    std::cout << "Singleton instance created with value: " << value_
              << ", name: " << name_ << '\n';
  }

  ~Singleton() = default;

  int value_;
  std::string name_;

  static Singleton *instance_; // Pointer to the Singleton instance
};

// Define the static member
Singleton *Singleton::instance_ = nullptr;

int main() {
  // Proper initialization
  Singleton::initialize(42, "FirstInstance");
  Singleton &instance1 = Singleton::getInstance();
  instance1.display();

  // Subsequent calls to initialize() have no effect
  Singleton::initialize(99, "IgnoredInstance");
  Singleton &instance2 = Singleton::getInstance();
  instance2.display();

  return 0;
}
