#ifndef __MEM_MEM_POOL_HPP__
#define __MEM_MEM_POOL_HPP__

#include <cstdlib>

template <typename A>
struct MemPoolRef {
  int index;
}

template <typename A>
struct MemPool {
  static A* pool = nullptr;
  static int freeIndex = 0;
  static int size = 0;
  static const int memPoolInitSize = 64;

  static initMemPool() {
    pool = (A*)malloc(sizeof(A) * memPoolInitSize);
    size = memPoolInitSize;
    freeIndex = 0;
  }

  static makeMemPoolLarger() {
    int newSize = size * 2;
    pool = (A*)realloc(sizeof(A) * newSize);
    size = newSize;
  }

  static MemPoolRef<A> alloc(A a) {
    if (pool == nullptr) { initMemPool(); }
    if (freeIndex == size) { makeMemPoolLarger(); }
    MemPoolRef<A> ref;
    ref.index = freeIndex;
    pool[ref.index] = a;
    ++freeIndex;
    return ref;
  }

  static void free(MemPoolRef<A> ref) {
    if (ref.index == freeIndex-1) {
      --freeIndex;
    } else {
      // TODO: Finish this. May need a 2nd array for index remapping.
    }
  }

  static A read(MemPoolRef<A> ref) {
    return pool[ref.index];
  }

  static void write(MemPoolRef<A> ref, A value) {
    pool[ref.index] = value;
  }
}

#endif // __MEM_MEM_POOL_HPP__
