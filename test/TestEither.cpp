#include "../data/Either.hpp"

#include <memory>

using namespace std;
using namespace highcpp_data;

class MyClassA {
public:
  MyClassA() {
    cout << "MyClassA constructor.";
  }
  virtual ~MyClassA() {
    cout << "MyClassA destructor.";
  }
};

class MyClassB {
public:
  MyClassB() {
    cout << "MyClassB constructor.";
  }
  virtual ~MyClassB() {
    cout << "MyClassB destructor.";
  }
};

static ostream& operator<<(ostream& os, const MyClassA& a) {
  return os << "MyClassA";
}

static ostream& operator<<(ostream& os, const MyClassB& b) {
  return os << "MyClassB";
}

int main() {
  auto x = Either<MyClassA,MyClassB>::right(MyClassB());
  cout << x << endl;
  return 0;
}
