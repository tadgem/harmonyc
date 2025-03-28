#pragma once

#include "EASTL/algorithm.h"
#include "EASTL/string.h"
#include "EASTL/unique_ptr.h"
#include "EASTL/unordered_map.h"
#include "EASTL/vector.h"
#include "Memory.h"
// TODO: find another way to handle async tasks
#include <future>
// TODO: find an alternative way of handling file io
#include <filesystem>

namespace harmony {
typedef eastl::basic_string<char, mimalloc_allocator> String;

template <typename T, typename Allocator = mimalloc_allocator>
using Vector = eastl::vector<T, Allocator>;

template <typename _Ty1, typename _Ty2> using Pair = eastl::pair<_Ty1, _Ty2>;

template <typename _Ty>
using Unique = eastl::unique_ptr<_Ty, mimalloc_default_delete<_Ty>>;

template <typename _Key, typename _Value>
using HashMap = eastl::unordered_map<_Key, _Value, eastl::hash<_Key>,
                                     eastl::equal_to<_Key>, mimalloc_allocator>;

template <typename _Ty, typename... Args>
Unique<_Ty> MakeUnique(Args &&...args) {
  void *memory_loc = mi_malloc(sizeof(_Ty));
  Unique<_Ty> ptr =
      Unique<_Ty>(new (memory_loc) _Ty(eastl::forward<Args>(args)...));
  return ptr;
}

template <typename _Ty> using Future = std::future<_Ty>;

// template utils
template <typename _Ty> static bool IsFutureReady(Future<_Ty> const &o) {
  return o.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
}

namespace Filesystem = std::filesystem;

namespace stl = eastl;

str_hash HashString(const String &input);
} // namespace harmony
