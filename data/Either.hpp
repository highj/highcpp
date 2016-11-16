#ifndef __DATA_EITHER_HPP__
#define __DATA_EITHER_HPP__

#include <functional>
#include <iostream>

namespace highcpp_data {

  template <typename A, typename B>
  class Either {
  public:

    static Either<A,B> left(A a) {
      B dummy;
      return Either(false, a, dummy);
    }

    static Either<A,B> right(B b) {
      A dummy;
      return Either(true, dummy, b);
    }

    template <typename C>
    C cata(std::function<C(const A&)> kLeft, std::function<C(const B&)> kRight) const {
      if (isRight) {
        return kRight(rightValue);
      } else {
        return kLeft(leftValue);
      }
    }

  private:
    bool isRight;
    A leftValue;
    B rightValue;

    Either(bool isRight, A leftValue, B rightValue): isRight(isRight), leftValue(leftValue), rightValue(rightValue) {}
  };

  template <typename A, typename B>
  static std::ostream& operator<<(std::ostream& os, const Either<A,B>& m) {
    m.cata(
      std::function<std::function<void()>(const A&)>([&](const A& a) {
        return [&]() {
          os << "Left " << a;
        };
      }),
      std::function<std::function<void()>(const B&)>([&](const B& b) {
        return [&]() {
          os << "Right " << b;
        };
      })
    )();
    return os;
  }

}

#endif // __DATA_EITHER_HPP__
