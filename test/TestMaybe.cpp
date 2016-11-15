#include <iostream>
#include <functional>

#include "../data/Maybe.hpp"

using namespace std;
using namespace highcpp_data;
using namespace highcpp_typeclass1;

// em++ -std=c++11 TestMaybe.cpp
int main() {
  auto a = Maybe<int>::just(3);
  auto b = Functor<Maybe>::map(std::function<int(const int&)>([](int x) { return x * 2; }), a);
  cout << b << endl;
  return 0;
}
