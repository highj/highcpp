#ifndef __DATA_MAYBE_HPP__
#define __DATA_MAYBE_HPP__

#include <functional>
#include <iostream>

#include "../typeclass1/Functor.hpp"
#include "../typeclass1/Apply.hpp"
#include "../typeclass1/Applicative.hpp"

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

namespace highcpp_typeclass1 {
  template<>
  struct Functor<highcpp_data::Maybe> {
    template <typename A, typename B>
    static highcpp_data::Maybe<B> map(std::function<B(const A&)> f, highcpp_data::Maybe<A> ma) {
      return ma.cata(
        highcpp_data::Maybe<B>::nothing(),
        std::function<highcpp_data::Maybe<B>(const A&)>([&](const A& a) {
          return highcpp_data::Maybe<B>::just(f(a));
        })
      );
    }
  };

  template<>
  struct Apply<highcpp_data::Maybe> {
    template <typename A, typename B>
    static highcpp_data::Maybe<B> apply(highcpp_data::Maybe<std::function<B(const A&)>> mf, highcpp_data::Maybe<A> ma) {
      return mf.cata(
        highcpp_data::Maybe<B>::nothing(),
        std::function<highcpp_data::Maybe<B>(const std::function<B(const A&)>&)>(
          [&](const std::function<B(const A&)>& f) {
            return map(f, ma);
          }
        )
      );
    }
  };

  template<>
  struct Applicative<highcpp_data::Maybe> {
    template <typename A>
    static highcpp_data::Maybe<A> pure(A a) {
      return highcpp_data::Maybe<A>::just(a);
    }
  };
}

#endif // __DATA_MAYBE_HPP__
