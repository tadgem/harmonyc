#include "EASTL/allocator_malloc.h"
#include "EASTL/vector.h"
#include "VkSDL.h"
#include "harmony_unity.cpp"
#include "lvk/lvk.h"
#include "memory.h"
#include <cstdio>

#define KILOBYTES(X) X * 1024ULL
#define MEGABYTES(X) X * 1024ULL * 1024ULL
#define GIGABYTES(X) X * 1024ULL * 1024ULL * 1024ULL

void *__cdecl operator new[](size_t size, const char *name, int flags,
                             unsigned debugFlags, const char *file, int line) {
  printf("Unassigned Allocation\n");
  return mi_malloc(size);
}

void *__cdecl operator new[](size_t size, unsigned __int64, unsigned __int64,
                             char const *, int, unsigned int, char const *,
                             int) {
  printf("Unassigned Allocation\n");
  return mi_malloc(size);
}

#define ALLOCATOR_TYPE allocator_malloc

using namespace eastl;

template <typename T> using Vector = eastl::vector<T, ALLOCATOR_TYPE>;

using namespace harmony;

int main() {
  uint64 size = GIGABYTES(4);
  Memory mem = Memory::Create<GIGABYTES(4)>();

  Vector<int32> intList(("int list"));
  intList.push_back(1);
  intList.push_back(2);
  intList.push_back(3);
  printf("intList size : %llu", intList.size());
  return 0;
}
