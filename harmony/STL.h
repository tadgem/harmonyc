#pragma once

#include <algorithm>
#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include "Memory.h"
#include <future>
#include <filesystem>



namespace harmony {
using String = std::basic_string<char, std::char_traits<char>, mi_stl_allocator<char>>;

template <typename _Ty, typename Allocator = mi_stl_allocator<_Ty>>
using Vector = std::vector<_Ty, Allocator>;

template <typename _Ty1, typename _Ty2> 
using Pair = std::pair<_Ty1, _Ty2>;

template <typename _Ty>
using Unique = std::unique_ptr<_Ty, mimalloc_default_delete<_Ty>>;

template <typename _Key, typename _Value>
using HashMap = std::unordered_map<_Key, _Value, std::hash<_Key>,
                                     std::equal_to<_Key>, mi_stl_allocator<std::pair<const _Key, _Value>>>;

template <typename _Ty, typename... Args>
Unique<_Ty> MakeUnique(Args &&...args) {
  void *memory_loc = mi_malloc(sizeof(_Ty));
  Unique<_Ty> ptr =
      Unique<_Ty>(new (memory_loc) _Ty(std::forward<Args>(args)...));
  return ptr;
}

template <typename _Ty> using Future = std::future<_Ty>;

// template utils
template <typename _Ty> static bool IsFutureReady(Future<_Ty> const &o) {
  return o.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
}

namespace Filesystem = std::filesystem;
namespace stl = std;

str_hash HashString(const String &input);
} // namespace harmony
