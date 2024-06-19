#include <stdexcept>
#include <stdio.h>

static int result;

int fibonacci(int i) {
  // Optimize the branch prediction
  if (i <= 1) [[unlikely]] {
    if (i < 0)
      throw std::runtime_error{"Negative number"};

    if (i == 0)
      return 0;
    return 1;
  }

  try {
    return fibonacci(i - 1) + fibonacci(i - 2);
  } catch (const std::exception &) {
    std::abort();
  }
}

int main() {
  try {
    for (int i = 0; i < 47; i++) {
      result = fibonacci(i);
    }
  } catch (const std::exception &) {
    std::abort();
  }
}
