#include <iostream>
#include <limits>
int main() {
  volatile int x = std::numeric_limits<int>::max();
  std::cout << x + 1 << '\n';
}
