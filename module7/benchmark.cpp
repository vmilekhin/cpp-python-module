#include <chrono>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <utility>

double distance_copy(std::vector<double> a, std::vector<double> b) {
  if (a.size() != b.size()) throw std::invalid_argument("size mismatch");
  double result = 0;
  for (std::size_t i = 0; i < a.size(); ++i) {
    double d = a[i] - b[i];
    result += d * d;
  }
  return result;
}

double distance_ref(const std::vector<double>& a, const std::vector<double>& b) {
  if (a.size() != b.size()) throw std::invalid_argument("size mismatch");
  double result = 0;
  for (std::size_t i = 0; i < a.size(); ++i) {
    double d = a[i] - b[i];
    result += d * d;
  }
  return result;
}

int main() {
  std::vector<double> a(4096, 1.5), b(4096, 0.5);
  constexpr int iterations = 20000;
  double sink = 0;
  auto t0 = std::chrono::steady_clock::now();
  for (int i = 0; i < iterations; ++i) sink += distance_copy(a, b);
  auto t1 = std::chrono::steady_clock::now();
  for (int i = 0; i < iterations; ++i) sink += distance_ref(a, b);
  auto t2 = std::chrono::steady_clock::now();
  auto ms = [](auto start, auto end) {
    return std::chrono::duration<double, std::milli>(end - start).count();
  };
  std::cout << "copy: " << ms(t0, t1) << " ms\n";
  std::cout << "const ref: " << ms(t1, t2) << " ms\n";
  std::cout << "checksum: " << sink << "\n";
}
