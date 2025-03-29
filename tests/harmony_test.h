#pragma once

#include <cstdio>

#include "EASTL/allocator_malloc.h"
#include "EASTL/vector.h"
#include "EASTL/unordered_map.h"
#include "EASTL/string.h"


#define FLECS_USE_OS_ALLOC
#include "flecs.h"
#include "flecs/addons/cpp/flecs.hpp"

#include "lvk/lvk.h"

#include "Assets.h"
#include "Engine.h"
#include "Json.h"
#include "Macros.h"
#include "Memory.h"
#include "STL.h"
#include "VkTech.h"
#include "harmony_unity.cpp"

namespace harmony {
enum class TestResultEnum { Fail = -1, Pass = 0, DNF = 1 };
struct TestResult {
  TestResultEnum mResult;
  harmony::String mResultMessage;
};
} // namespace harmony

#define TEST_ASSERT(cond, message, ...)                                        \
  if (!(cond)) {                                                               \
    HNY_LOG_ERROR(message, __VA_ARGS__);                                       \
    return harmony::TestResultEnum::Fail;                                      \
  }                                                                            \
  
#define HARMONY_OVERRIDE_GLOBAL_NEW_TESTS(ENABLE_PRINT)                        \
  void *__cdecl operator new[](size_t size, const char *name, int flags,       \
                               unsigned debugFlags, const char *file,          \
                               int line) {                                     \
    ENABLE_PRINT ? printf("Unassigned Allocation!\n") : 0;                     \
    return std::malloc(size);                                                    \
  }                                                                            \
                                                                               \
  void *__cdecl operator new[](size_t size, unsigned __int64,                  \
                               unsigned __int64, char const *, int,            \
                               unsigned int, char const *, int) {              \
    ENABLE_PRINT ? printf("Unassigned Allocation!\n") : 0;                     \
    return std::malloc(size);                                                    \
  }


#define TEST_APP_BEGIN(suite_name) \
HARMONY_OVERRIDE_GLOBAL_NEW_TESTS(false)\
int main() {\
eastl::unordered_map<eastl::string, harmony::TestResultEnum> sResults{};\
eastl::string sCurrentTestName = "";\
HNY_LOG_INFO("%s Tests\n", suite_name);

#define TEST_APP_END() for(auto [name, result] : sResults) {\
    HNY_LOG_INFO("Test %s, Result : %s \n", name.c_str(), result == harmony::TestResultEnum::Fail ? "Fail" : "Pass");\
}};

using TestFunction = harmony::TestResultEnum (*)(harmony::Engine* engine);

#define ADD_TEST(test_name) sResults[#test_name] = test_name();

