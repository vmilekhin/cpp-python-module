#include <iostream>
#include <thread>
int main() {
  int counter = 0;
  auto f = [&] { for (int i=0; i<100000; ++i) ++counter; };
  std::thread a(f), b(f);
  a.join(); b.join();
  std::cout << counter << '\n';
}
