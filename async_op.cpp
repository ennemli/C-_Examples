#include <chrono>
#include <coroutine>
#include <future>
#include <iostream>
#include <thread>

using namespace std;

// Simulate an asynchronous operation, like reading data from a file
std::future<std::string> async_read_data() {
  return std::async(std::launch::async, [] {
    // Simulate I/O delay
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return std::string("Data read from file");
  });
}

// Awaiter for std::future to make it coroutine-compatible
template <typename T> struct future_awaiter {
  std::future<T> &fut;

  future_awaiter(std::future<T> &fut) : fut(fut) {}

  bool await_ready() const noexcept {
    return fut.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
  }

  void await_suspend(std::coroutine_handle<> handle) {
    // Continue the coroutine when the future is ready
    std::thread([this, handle]() {
      fut.wait(); // Wait for the future to be ready
      handle.resume();
    }).detach();
  }

  T await_resume() {
    return fut.get(); // Return the result of the future
  }
};

// Coroutine that performs an async file read operation
struct Task {
  struct promise_type;
  using handle_type = std::coroutine_handle<promise_type>;

  struct promise_type {
    Task get_return_object() { return Task{handle_type::from_promise(*this)}; }

    std::suspend_never initial_suspend() { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }

    void return_value(const std::string &value) { result = value; }
    void unhandled_exception() { std::exit(1); }

    std::string result;
  };

  handle_type coro_handle;
  Task(handle_type h) : coro_handle(h) {}
  ~Task() { coro_handle.destroy(); }

  void resume() { coro_handle.resume(); }

  std::string result() { return coro_handle.promise().result; }
};

// Coroutine that performs an async file read
Task async_file_read() {
  std::cout << "Starting asynchronous file read..." << std::endl;

  // Perform an async operation, and co_await on it
  std::string data = co_await future_awaiter<std::string>{async_read_data()};

  std::cout << "File read complete: " << data << std::endl;
  co_return data;
}

int main() {
  Task task = async_file_read(); // Start the coroutine

  // Simulate doing other work while the coroutine runs asynchronously
  std::cout << "Main thread doing other work..." << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(1));

  task.resume(); // Resume the coroutine once the async operation is done

  // Print the result of the coroutine once it's finished
  std::cout << "Received from coroutine: " << task.result() << std::endl;

  return 0;
}

