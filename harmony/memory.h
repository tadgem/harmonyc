#pragma once
#include "EASTL/allocator.h"
#include "Primitives.h"
#include "Macros.h"
#include "mimalloc.h"

/// <summary>
/// Macro to globally override new
/// Used to track non-allocator'd code
/// while still use the upfront page we create for the engine
/// </summary>
#define HARMONY_OVERRIDE_GLOBAL_NEW(ENABLE_PRINT)                              \
  void *__cdecl operator new[](size_t size, const char *name, int flags,       \
                               unsigned debugFlags, const char *file,          \
                               int line) {                                     \
    ENABLE_PRINT ? printf("Unassigned Allocation!\n") : 0;                     \
    HNY_ASSERT_NOT_REACHED();                                                  \
    return mi_malloc(size);                                                    \
  }                                                                            \
                                                                               \
  void *__cdecl operator new[](size_t size, unsigned __int64,                  \
                               unsigned __int64, char const *, int,            \
                               unsigned int, char const *, int) {              \
    ENABLE_PRINT ? printf("Unassigned Allocation!\n") : 0;                     \
    HNY_ASSERT_NOT_REACHED();                                                  \
    return mi_malloc(size);                                                    \
  }

#define HNY_NEW(Type, ...) new(mi_malloc(sizeof(Type))) Type(__VA_ARGS__)
#define HNY_DELETE(Obj) mi_free(Obj)

namespace harmony {
class mimalloc_allocator {
public:
  EASTL_ALLOCATOR_EXPLICIT
  mimalloc_allocator(const char *pName = "mimalloc_allocator") {}
  mimalloc_allocator(const mimalloc_allocator &x) {}
  mimalloc_allocator(const mimalloc_allocator &x, const char *pName) {}

  mimalloc_allocator &operator=(const mimalloc_allocator &x) { return *this; }

  void *allocate(size_t n, int flags = 0) { return mi_malloc(n); }

  void *allocate(size_t n, size_t alignment, size_t offset, int flags = 0) {
    return mi_malloc_aligned_at(n, alignment, offset);
  }

  void deallocate(void *p, size_t n) {
    // TODO: Verify n is size and not alignment specifier
    return mi_free_size(p, n);
  }

  const char *get_name() const { return "mimalloc_allocator"; }
  void set_name(const char *pName) {};

protected:
#if EASTL_NAME_ENABLED
  const char *pName; // Debug name, used to track memory.
#endif
};

template <class T> struct STLMimallocAllocator {
  typedef T value_type;

  STLMimallocAllocator() {} // default ctor not required by C++ Standard Library

  // A converting copy constructor:
  template <class U> STLMimallocAllocator(const STLMimallocAllocator<U> &o) {}
  template <class U> bool operator==(const STLMimallocAllocator<U> &) const {
    return true;
  }
  template <class U> bool operator!=(const STLMimallocAllocator<U> &) const {
    return false;
  }
  T *allocate(const size_t n) const {
    return static_cast<T *>(mi_malloc(sizeof(T)));
  }
  void deallocate(T *const p, size_t) const { mi_free((void *)p); }
};

template <typename T> class mimalloc_default_delete {
public:
  void operator()(T *p) const EA_NOEXCEPT { mi_free((void *)p); }
};

/// <summary>
/// Global struct creating memory and
/// allowing creation of sub allocators for specific use cases
/// </summary>
struct Memory {
  inline static uint64        sAllocatedBytes = 0;
  inline static void*         sMemory = nullptr;
  mi_arena_id_t mArenaId;
  mi_heap_t*    mHeap;
  mi_heap_t*    mPreviousHeap;

  void Free()
  {
      mi_heap_set_default(mPreviousHeap);

      // TODO: Investigate releasing a heap properly.
      // mi_heap_delete(mHeap);
      
      memset(sMemory, 0, static_cast<size_t>(sAllocatedBytes));
  }

  static void FreeGlobal()
  {
      std::free(sMemory);
  }

  static void InitGlobal(uint64 upfrontMemory)
  {
      if (sMemory == nullptr)
      {
          sMemory = std::malloc(upfrontMemory);
          sAllocatedBytes = upfrontMemory;
          memset(sMemory, 0, sAllocatedBytes);
          mi_option_set(mi_option_show_errors, 1);
          mi_option_set(mi_option_verbose, 1);
          mi_option_set(mi_option_arena_eager_commit, 1);
          mi_option_set(mi_option_purge_delay, 0);
          mi_option_set(mi_option_purge_decommits, 0);
          mi_option_set(mi_option_allow_large_os_pages, 1);
      }
  }

  static Memory Create(uint64 upfrontMemory) {
    
    if (sMemory == nullptr)
    {
        InitGlobal(upfrontMemory);
    }

    mi_arena_id_t   arenaId;
    constexpr bool  is_committed = true;
    constexpr bool  is_large = true;
    constexpr bool  is_exclusive = true;
    constexpr bool  is_zeroed = true;
    constexpr int   numa_mode = -1;
    mi_manage_os_memory_ex(sMemory, upfrontMemory, is_committed, is_large,
                           is_zeroed, numa_mode, is_exclusive, &arenaId);

    mi_heap_t* engineHeap   = mi_heap_new_in_arena(arenaId);
    mi_heap_t* previousHeap = mi_heap_get_default();
    mi_heap_set_default(engineHeap);

    return Memory{arenaId, engineHeap, previousHeap};
  }
};
} // namespace harmony
