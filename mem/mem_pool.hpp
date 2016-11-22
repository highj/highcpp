#ifndef __MEM_MEM_POOL_HPP__
#define __MEM_MEM_POOL_HPP__

#include <iostream>
#include <cstdlib>

namespace highcpp_mem {

  template <typename A>
  struct MemPool;

  template <typename A>
  struct MemPoolRef {
    MemPoolRef(): index(-1) {}

    MemPoolRef(int index): index(index) {}

    MemPoolRef(MemPoolRef&& ref) {
      index = ref.index;
      ref.index = -1;
    }

    MemPoolRef(const MemPoolRef<A>& other): index(MemPool<A>::alloc(other.read())) {
    }

    ~MemPoolRef() {
      if (index != -1) {
        MemPool<A>::free(index);
      }
    }

    MemPoolRef<A>& operator=(const MemPoolRef<A>& other) {
      MemPool<A>::free(index);
      index = MemPool<A>::alloc(other.read());
      return *this;
    }

    static MemPoolRef<A> of(A a) {
      MemPoolRef<A> ref(MemPool<A>::alloc(a));
      return ref;
    }

    const A& read() const {
      return MemPool<A>::read(index);
    }
  private:
    friend struct MemPool<A>;

    int index;
  };

  template <typename A>
  struct MemPool {

    static void logState() {
      using namespace std;
      cout << "Mem Pool State" << endl;
      cout << "Pool Capacity: " << poolCapacity << endl;
      cout << "Pool Size: " << poolSize << endl;
      cout << "Free Indices Capacity: " << freeIndicesCapacity << endl;
      cout << "Free Indices Size: " << freeIndicesSize << endl;
      cout << "Free Indices: [";
      for (int i = 0; i < freeIndicesSize; ++i) {
        if (i != 0) { cout << ", "; }
        cout << freeIndices[i];
      }
      cout << "]" << endl;
    }

  private:
    friend struct MemPoolRef<A>;

    static A* pool;
    static int* freeIndices;
    static int poolCapacity;
    static int poolSize;
    static int freeIndicesCapacity;
    static int freeIndicesSize;
    static const int poolInitSize = 64;
    static const int freeIndicesInitSize = 64;

    static int alloc(A a) {
      if (pool == nullptr) { initMemPool(); }
      if (hasFreeIndex()) {
        int index = popFreeIndex();
        pool[index] = a;
        return index;
      } else {
        if (poolSize == poolCapacity) { makeMemPoolLarger(); }
        int index = poolSize++;
        pool[index] = a;
        return index;
      }
    }

    static void free(int index) {
      pushFreeIndex(index);
    }

    static const A& read(int index) {
      return pool[index];
    }

    static void write(int index, A value) {
      pool[index] = value;
    }

    static void initMemPool() {
      pool = (A*)malloc(sizeof(A) * poolInitSize);
      freeIndices = (int*)malloc(sizeof(int) * freeIndicesInitSize);
      poolCapacity = poolInitSize;
      freeIndicesCapacity = freeIndicesInitSize;
    }

    static void makeMemPoolLarger() {
      int newPoolCapacity = poolCapacity * 2;
      pool = (A*)realloc(pool, sizeof(A) * newPoolCapacity);
      poolCapacity = newPoolCapacity;
    }

    static void makeFreeIndicesLarger() {
      int newFreeIndicesCapacity = freeIndicesCapacity * 2;
      freeIndices = (int*)realloc(freeIndices, sizeof(int) * newFreeIndicesCapacity);
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
  };

  template <typename A>
  A* MemPool<A>::pool = nullptr;

  template <typename A>
  int* MemPool<A>::freeIndices = nullptr;

  template <typename A>
  int MemPool<A>::poolCapacity = 0;

  template <typename A>
  int MemPool<A>::poolSize = 0;

  template <typename A>
  int MemPool<A>::freeIndicesCapacity = 0;

  template <typename A>
  int MemPool<A>::freeIndicesSize = 0;

}

#endif // __MEM_MEM_POOL_HPP__
