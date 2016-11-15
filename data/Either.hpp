#include <functional>
#include <iostream>

namespace highcpp_data {

  template <typename A, typename B>
  union __EitherValue {
    A leftValue;
    B rightValue;
  };

  template <typename A, typename B>
  class Either {
  public:

    static Either<A,B> left(A a) {
      __EitherValue<A,B> value;
      value.leftValue = a;
      return Either(false, value);
    }

    static Either<A,B> right(B b) {
      __EitherValue<A,B> value;
      value.rightValue = b;
      return Either(true, value);
    }

    template <typename C>
    C cata(std::function<C(const A&)> kLeft, std::function<C(const B&)> kRight) const {
      if (isRight) {
        return kRight(value.rightValue);
      } else {
        return kLeft(value.leftValue);
      }
    }

  private:
    bool isRight;
    __EitherValue<A,B> value;

    Either(bool isRight, __EitherValue<A,B> value): isRight(isRight), value(value) {}
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
