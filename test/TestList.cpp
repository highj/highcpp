#include "../data/List.hpp"

using namespace highcpp_data;
using namespace highcpp_mem;

int main() {
  List<int> list =
    List<int>::cons(1,
      MemPoolRef<List<int>>::of(List<int>::cons(2,
        MemPoolRef<List<int>>::of(List<int>::cons(3,
          MemPoolRef<List<int>>::of(List<int>::nil())
        ))
      ))
    );
  return 0;
}
