#ifndef __DATA_LIST_HPP__
#define __DATA_LIST_HPP__

#include <tuple>
#include "Maybe.hpp"
#include "../mem/mem_pool.hpp"
#include "../util/traits.hpp"

namespace highcpp_data {

  using namespace highcpp_mem;
  using namespace highcpp_util;

  template <typename A>
  struct List {

    static List<A> nil() {
      return List<A>(Maybe<std::tuple<A,MemPoolRef<List<A>>>>::nothing());
    }

    static List<A> cons(A head, MemPoolRef<List<A>> tail) {
      return List<A>(Maybe<std::tuple<A,MemPoolRef<List<A>>>>::just(std::tuple<A,MemPoolRef<List<A>>>(head, tail)));
    }

    template <typename F>
    typename lambda_traits<F>::return_type cata(
      typename lambda_traits<F>::return_type kNil,
      F kCons
    ) {
      return unList.cata(kNil, kCons);
    }

    List(const List<A>& other): unList(other.unList) {
    }

  private:
    Maybe<std::tuple<A,MemPoolRef<List<A>>>> unList;

    List(Maybe<std::tuple<A,MemPoolRef<List<A>>>> unList): unList(unList) {}
  };

}

#endif // __DATA_LIST_HPP__
