#include <coroutine>
#include <iostream>

template <typename T> struct RObj {
  struct promise_type {
    T value_;
    ~promise_type() { std::cout << "promise_type destroyed" << std::endl; }
    RObj<T> get_return_object() {
      return {.h_ = std::coroutine_handle<promise_type>::from_promise(*this)};
    };
    std::suspend_never initial_suspend() { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }
    void unhandled_exception() {}
    std::suspend_always yield_value(T value) {
      value_ = value;
      return {};
    }
    void return_void() {}
  };
  std::coroutine_handle<promise_type> h_;
  operator std::coroutine_handle<promise_type>() { return h_; }
  operator std::coroutine_handle<>() const { return h_; }
};

RObj<int> coroutine() {
  for (int i = 0; i < 3; ++i) {
    co_yield i;
  }
}

int main(int argc, char *argv[]) {
  std::coroutine_handle<RObj<int>::promise_type> h = coroutine();
  RObj<int>::promise_type &pp = h.promise();
  while (!h.done()) {
    std::cout << "Main loop " << pp.value_ << " h:" << &h << " times\n";
    h();
  }

  return 0;
}
