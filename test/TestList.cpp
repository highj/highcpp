#include "../data/List.hpp"

using namespace highcpp_data;
using namespace highcpp_mem;

int main() {
  MemPoolRef<List<int>> a = MemPoolRef<List<int>>::of(List<int>::nil());
  MemPoolRef<List<int>> b = MemPoolRef<List<int>>::of(List<int>::cons(3, a));
  MemPoolRef<List<int>> c = MemPoolRef<List<int>>::of(List<int>::cons(2, b));
  List<int> d = List<int>::cons(1, c);
  MemPool<List<int>>::logState();
  return 0;
}
