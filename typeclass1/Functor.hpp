#ifndef __TYPECLASS1_FUNCTOR_HPP__
#define __TYPECLASS1_FUNCTOR_HPP__

#include <functional>

namespace highcpp_typeclass1 {

  template <template <typename> class M>
  struct Functor {
    template <typename A, typename B>
    static M<B> map(std::function<B(const A&)> f, M<A> ma);
  };

  // helper method (to reduce noise)
  template <template <typename> class M, typename A, typename B>
  static M<B> map(std::function<B(const A&)> f, M<A> ma) {
    return Functor<M>::map(f, ma);
  }
}

#endif // __TYPECLASS1_FUNCTOR_HPP__
