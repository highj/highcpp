#include <iostream>
#include <functional>

#include "../data/Maybe.hpp"

using namespace std;
using namespace highcpp_data;
using namespace highcpp_typeclass1;

// em++ -std=c++11 TestMaybe.cpp
int main() {
  auto a = Maybe<int>::just(3);
  auto b = map(std::function<int(const int&)>([](int x) { return x * 2; }), a);
  auto c = map2(
    std::function<int(const int&,const int&)>(
      [](int x, int y) {
        return x + y;
      }
    ),
    a,
    b
  );
  cout << c << endl;
  return 0;
}
