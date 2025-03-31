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
#include "Timer.h"
#include "VkTech.h"
#include "harmony_unity.cpp"

namespace harmony {
enum class TestResultEnum { Fail = -1, Pass = 0, DNF = 1 };
struct TestResult {
  TestResultEnum    mResult;
  harmony::String   mResultMessage;
  f64               mElapsedMs;

  static TestResult Pass() { return { TestResultEnum::Pass, {}, 0.0 }; };
};
} // namespace harmony

#define TEST_ASSERT(cond, message, ...)                                        \
  if (!(cond)) {                                                               \
    HNY_LOG_ERROR(message, __VA_ARGS__);                                       \
    return TestResult { harmony::TestResultEnum::Fail, ##message, 0.0};         \
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
eastl::unordered_map<eastl::string, harmony::TestResult> sResults{};\
eastl::string sCurrentTestName = "";\
HNY_LOG_INFO("%s Tests\n", suite_name);

#define TEST_APP_END() for(auto [name, result] : sResults) {\
    HNY_LOG_INFO("Test %s, Result : %s, Time Taken : %f ms\n", name.c_str(), result.mResult == harmony::TestResultEnum::Fail ? "Fail" : "Pass", result.mElapsedMs);\
    if(result.mResult != harmony::TestResultEnum::Pass) { HNY_LOG_INFO("    Test Message : %s\n", result.mResultMessage.c_str());}\
}};

#define ADD_TEST(test_name) sResults[#test_name] = test_name();

#define ADD_TEST2(TEST_NAME) harmony::Timer timer_##TEST_NAME;\
auto result_##TEST_NAME = TEST_NAME();\
f64 time_taken_##TEST_NAME = timer_##TEST_NAME.ElapsedMillisecondsF();\
result_##TEST_NAME.mElapsedMs = time_taken_##TEST_NAME;\
sResults[#TEST_NAME] = result_##TEST_NAME;
