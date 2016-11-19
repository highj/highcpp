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
  static int* freeIndices = nullptr;
  static int poolCapacity = 0;
  static int poolSize = 0;
  static int freeIndicesCapacity = 0;
  static inf freeIndicesSize = 0;
  static const int poolInitSize = 64;
  static const int freeIndicesInitSize = 64;

  static MemPoolRef<A> alloc(A a) {
    if (pool == nullptr) { initMemPool(); }
    if (hasFreeIndex()) {
      MemPoolRef<A> ref;
      ref.index = popFreeIndex();
      pool[ref.index] = a;
      return ref;
    } else {
      if (poolSize == poolCapacity) { makeMemPoolLarger(); }
      MemPoolRef<A> ref;
      ref.index = poolSize++;
      pool[ref.index] = a;
      return ref;
    }
  }

  static void free(MemPoolRef<A> ref) {
    pushFreeIndex(ref.index);
  }

  static A read(MemPoolRef<A> ref) {
    return pool[ref.index];
  }

  static void write(MemPoolRef<A> ref, A value) {
    pool[ref.index] = value;
  }

private:
  static void initMemPool() {
    pool = (A*)malloc(sizeof(A) * poolInitSize);
    freeIndices = (int*)malloc(sizeof(int) * freeIndicesInitSize);
    poolCapacity = memPoolInitSize;
    freeIndicesCapacity = freeIndicesInitSize;
    freeIndex = 0;
  }

  static void makeMemPoolLarger() {
    int newPoolCapacity = poolCapacity * 2;
    pool = (A*)realloc(sizeof(A) * newPoolCapacity);
    poolCapacity = newPoolCapacity;
  }

  static void makeFreeIndicesLarger() {
    int newFreeIndicesCapacity = freeIndicesCapacity * 2;
    freeIndices = (int*)realloc(sizeof(int) * newFreeIndicesCapacity);
    freeIndicesCapacity = newFreeIndicesCapacity;
  }

  static bool hasFreeIndex() {
    return freeIndicesSize > 0;
  }

  static void pushFreeIndex(int freeIndex) {
    if (freeIndicesSize == freeIndicesCapacity) {
      makeFreeIndicesLarger();
    }
    freeIndices[freeIndicesSize++] = freeIndex;
  }

  static int popFreeIndex() {
    return freeIndices[--freeIndicesSize];
  }
}

#endif // __MEM_MEM_POOL_HPP__
