#include <stdio.h>
#include <stdlib.h>

static int result;

int fibonacci(int i) {
  if (i <= 1) {
    if (i < 0)
      abort();
    if (i == 0)
      return 0;
    return 1;
  }
  return fibonacci(i - 1) + fibonacci(i - 2);
}

int main() {
  for (int i = 0; i < 47; i++) {
    result = fibonacci(i);
  }
}
