#include <functional>
#include <iostream>

namespace highcpp_data {

  template <typename A>
  class Maybe {
  public:

    static Maybe<A> just(A a) {
      return Maybe(a);
    }

    static Maybe<A> nothing() {
      return Maybe();
    }

    template <typename B>
    B cata(B kNothing, std::function<B(const A&)> kJust) const {
      if (hasValue) {
        return kJust(value);
      } else {
        return kNothing;
      }
    }

  private:
    bool hasValue;
    A value;

    Maybe(): hasValue(false) {}

    Maybe(A a): hasValue(true), value(a) {}
  };

  template <typename A>
  static std::ostream& operator<<(std::ostream& os, const Maybe<A>& m) {
    m.cata(
      std::function<void()>([&]() {
        os << "Nothing";
      }),
      std::function<std::function<void()>(const A&)>([&](const A& a) {
        return [&]() {
          os << "Just " << a;
        };
      })
    )();
    return os;
  }

}
