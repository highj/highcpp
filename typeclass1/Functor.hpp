#ifndef __TYPECLASS1_FUNCTOR_HPP__
#define __TYPECLASS1_FUNCTOR_HPP__

#include <functional>
#include <type_traits>
#include "../util/traits.hpp"

namespace highcpp_typeclass1 {

  template <template <typename> class M>
  struct Functor {
    template <typename A, typename F>
    static M<typename highcpp_util::lambda_traits<F>::result_type> map(F f, M<A> ma);
  };

  // helper method (to reduce noise)
  template <template <typename> class M, typename A, typename F>
  static M<typename highcpp_util::lambda_traits<F>::result_type> map(F f, M<A> ma) {
    return Functor<M>::map(f, ma);
  }
}

#endif // __TYPECLASS1_FUNCTOR_HPP__
