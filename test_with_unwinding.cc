#include <stdexcept>
#include <stdio.h>
#include <vector>

static int result;

int fibonacci(int i)
#ifdef unwind_noexcept
    noexcept
#endif
{
  // Make sure there is stack unwinding code
  std::vector<int> r{0, 0};

  // Optimize the branch prediction
  if (i <= 1) [[unlikely]] {
    if (i < 0)
#if defined(unwind_throwing) || defined(unwind_catching)
      throw std::runtime_error{"Negative number"};
#else
      std::abort();
#endif

    if (i == 0)
      return 0;
    return 1;
  }

#ifdef unwind_catching
  try {
#endif
    r[0] = fibonacci(i - 1);
    r[1] = fibonacci(i - 2);
    return r[0] + r[1];
#ifdef unwind_catching
  } catch (const std::exception &) {
    std::abort();
  }
#endif
}

int main() {
#if defined(unwind_throwing) || defined(unwind_catching)
  try {
#endif
    for (int i = 0; i < 40; i++) {
      result = fibonacci(i);
    }
#if defined(unwind_throwing) || defined(unwind_catching)
  } catch (const std::exception &) {
    std::abort();
  }
#endif
}
