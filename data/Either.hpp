#ifndef __DATA_EITHER_HPP__
#define __DATA_EITHER_HPP__

#include <functional>
#include <iostream>
#include "../mem/mem_pool.hpp"

namespace highcpp_data {

  using namespace highcpp_mem;

  template <typename A, typename B>
  class Either {
  public:

    static Either<A,B> left(const A& a) {
      return Either(false, MemPool<A>::alloc(a));
    }

    static Either<A,B> right(const B& b) {
      return Either(true, MemPool<B>::alloc(b));
    }

    template <typename C>
    C cata(std::function<C(const A&)> kLeft, std::function<C(const B&)> kRight) const {
      if (isRight) {
        return kRight(MemPool<B>::read(memPoolIndex));
      } else {
        return kLeft(MemPool<A>::read(memPoolIndex));
      }
    }

    ~Either() {
      if (isRight) {
        MemPool<B>::free(memPoolIndex);
      } else {
        MemPool<A>::free(memPoolIndex);
      }
    }

  private:
    bool isRight;
    int memPoolIndex;

    Either(bool isRight, int memPoolIndex): isRight(isRight), memPoolIndex(memPoolIndex) {}
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

#endif // __DATA_EITHER_HPP__
