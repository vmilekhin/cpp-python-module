#include <iostream>
int main() {
  int* a = new int[3]{1,2,3};
  std::cout << a[3] << '\n'; // выход за границу
  delete[] a;
}
