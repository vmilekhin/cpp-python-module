int main() {
  int* p = new int[100];
  p[0] = 42;
  return p[0] == 42 ? 0 : 1;
}
