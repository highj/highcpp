#ifndef __DATA_MAYBE_HPP__
#define __DATA_MAYBE_HPP__

#include <functional>
#include <iostream>

#include "../mem/mem_pool.hpp"
#include "../typeclass1/Functor.hpp"
#include "../typeclass1/Apply.hpp"
#include "../typeclass1/Applicative.hpp"
#include "../typeclass1/Bind.hpp"

namespace highcpp_data {

  using namespace highcpp_mem;

  template <typename A>
  class Maybe {
  public:

    static Maybe<A> just(const A& a) {
      return Maybe(a);
    }

    static Maybe<A> nothing() {
      return Maybe();
    }

    template <typename B>
    B cata(B kNothing, std::function<B(const A&)> kJust) const {
      if (memPoolIndex == -1) {
        return kNothing;
      } else {
        return kJust(MemPool<A>::read(memPoolIndex));
      }
    }

    Maybe(const Maybe<A>& other) {
      if (other.memPoolIndex == -1) {
        memPoolIndex = -1;
      } else {
        memPoolIndex = MemPool<A>::alloc(MemPool<A>::read(other.memPoolIndex));
      }
    }

    ~Maybe() {
      if (memPoolIndex != -1) {
        MemPool<A>::free(memPoolIndex);
      }
    }

  private:
    int memPoolIndex;

    Maybe(): memPoolIndex(-1) {}

    Maybe(const A& a): memPoolIndex(MemPool<A>::alloc(a)) {}
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
    template <typename A, typename F>
    static highcpp_data::Maybe<typename highcpp_util::lambda_traits<F>::result_type> map(F f, highcpp_data::Maybe<A> ma) {
      using B = typename highcpp_util::lambda_traits<F>::result_type;
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
    template <typename A, typename F>
    static highcpp_data::Maybe<typename highcpp_util::lambda_traits<F>::result_type> apply(highcpp_data::Maybe<F> mf, highcpp_data::Maybe<A> ma) {
      using B = typename highcpp_util::lambda_traits<F>::result_type;
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

  template<>
  struct Bind<highcpp_data::Maybe> {
    template <typename A, typename F>
    static typename highcpp_util::lambda_traits<F>::result_type bind(highcpp_data::Maybe<A> ma, F f) {
      using MB = typename highcpp_util::lambda_traits<F>::result_type;
      return ma.cata(
        MB::nothing(),
        std::function<MB(const A&)>([=](const A& a) {
          return f(a);
        })
      );
    }
  };
}

#endif // __DATA_MAYBE_HPP__
