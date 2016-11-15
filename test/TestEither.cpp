#include "../data/Either.hpp"

using namespace std;
using namespace highcpp_data;

int main() {
  Either<int,float> x = Either<int,float>::right(6.2f);
  cout << x;
  return 0;
}
