#include "../data/Either.hpp"

#include <memory>

using namespace std;
using namespace highcpp_data;

class MyClassA {
public:
  MyClassA() {
    cout << "MyClassA constructor." << endl;
  }
  MyClassA(const MyClassA&) {
    cout << "MyClassA constructor." << endl;
  }
  virtual ~MyClassA() {
    cout << "MyClassA destructor." << endl;
  }
};

class MyClassB {
public:
  MyClassB() {
    cout << "MyClassB constructor." << endl;
  }
  MyClassB(const MyClassB&) {
    cout << "MyClassB constructor." << endl;
  }
  virtual ~MyClassB() {
    cout << "MyClassB destructor." << endl;
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
