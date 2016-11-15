#include <iostream>
#include "../data/Maybe.hpp"

using namespace std;
using namespace highcpp_data;

// em++ -std=c++11 TestMaybe.cpp
int main() {
  Maybe<int> a = Maybe<int>::just(3);
  cout << a << endl;
  return 0;
}
