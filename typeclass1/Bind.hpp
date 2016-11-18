#ifndef __TYPECLASS1_BIND_HPP__
#define __TYPECLASS1_BIND_HPP__

#include "../util/traits.hpp"

namespace highcpp_typeclass1 {

  template <template <typename> class M>
  struct Bind {
    template <typename A, typename F>
    static typename highcpp_util::lambda_traits<F>::result_type bind(M<A> ma, F f);
  };

  template <template <typename> class M, typename A, typename F>
  static typename highcpp_util::lambda_traits<F>::result_type bind(M<A> ma, F f) {
    return Bind<M>::bind(ma, f);
  }

  template <template <typename> class M, typename A, typename F>
  static typename highcpp_util::lambda_traits<F>::result_type operator>>=(M<A> ma, F f) {
    return bind(ma, f);
  }
}

#endif // __TYPECLASS1_BIND_HPP__
