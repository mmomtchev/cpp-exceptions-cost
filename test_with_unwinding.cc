#include <stdexcept>
#include <stdio.h>

static int objects;

class IntWithDestructor {
  int val;

public:
  IntWithDestructor() : val{} { objects++; }
  ~IntWithDestructor() { objects--; }
  int operator=(int rhs) {
    val = rhs;
    return val;
  }
  operator int() { return val; }
};

static int result;

int fibonacci(int i)
#ifdef unwind_noexcept
    noexcept
#endif
{
  // Make sure there is stack unwinding code
  IntWithDestructor a, b;

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
    a = fibonacci(i - 1);
    b = fibonacci(i - 2);
    return (int)a + (int)b;
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
    for (int i = 0; i < 46; i++) {
      result = fibonacci(i);
    }
#if defined(unwind_throwing) || defined(unwind_catching)
  } catch (const std::exception &) {
    std::abort();
  }
#endif
}
