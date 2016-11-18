#ifndef __TYPECLASS1_APPLY_HPP__
#define __TYPECLASS1_APPLY_HPP__

#include <functional>
#include "Functor.hpp"
#include "../util/traits.hpp"

namespace highcpp_typeclass1 {

  template <template <typename> class M>
  struct Apply {
    template <typename A, typename F>
    static M<typename highcpp_util::lambda_traits<F>::result_type> apply(M<F> mf, M<A> ma);
  };

  template <template <typename> class M, typename A, typename F>
  static M<typename highcpp_util::lambda_traits<F>::result_type> apply(M<F> mf, M<A> ma) {
    return Apply<M>::apply(mf, ma);
  }

  template <template <typename> class M, typename A, typename B, typename C>
  static M<C> map2(std::function<std::function<C(const B&)>(const A&)> f, M<A> ma, M<B> mb) {
    return apply(map(f, ma), mb);
  }

  template <template <typename> class M, typename A, typename B, typename C>
  static M<C> map2(std::function<C(const A&, const B&)> f, M<A> ma, M<B> mb) {
    return map2(
      std::function<std::function<C(const B&)>(const A&)>(
        [f](const A& a) {
          return std::function<C(const B&)>(
            [f,a](const B& b) {
              return f(a,b);
            }
          );
        }
      ),
      ma,
      mb
    );
  }

}

#endif // __TYPECLASS1_APPLY_HPP__
