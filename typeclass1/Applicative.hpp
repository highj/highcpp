#ifndef __TYPECLASS1_APPLICATIVE_HPP__
#define __TYPECLASS1_APPLICATIVE_HPP__

namespace highcpp_typeclass1 {

  template <template <typename> class M>
  struct Applicative {
    template <typename A>
    static M<A> pure(A a);
  };

}

#endif // __TYPECLASS1_APPLICATIVE_HPP__
