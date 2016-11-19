#include <iostream>

#include "../mem/mem_pool.hpp"

using namespace std;
using namespace highcpp_mem;

int main() {
  {
    cout << "---" << endl;
    MemPool<int>::logState();
    MemPoolRef<int> a = MemPoolRef<int>::of(5);
    MemPoolRef<int> b = MemPoolRef<int>::of(6);
    MemPoolRef<int> c = MemPoolRef<int>::of(7);
    cout << "---" << endl;
    MemPool<int>::logState();
  }
  cout << "---" << endl;
  MemPool<int>::logState();
  cout << "---" << endl;
}
