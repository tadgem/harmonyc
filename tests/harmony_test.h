#pragma once
#include <cstdio>
#include "EASTL/allocator_malloc.h"
#include "EASTL/vector.h"
#include "EASTL/map.h"
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

using TestString = eastl::basic_string<char, eastl::allocator_malloc>;

template<typename _Key, typename _Value>
using TestHashMap = eastl::map<
    _Key,
    _Value,
    eastl::equal_to<_Key>,
    eastl::allocator_malloc>;

struct TestResult {
    TestResultEnum    mResult;
    TestString        mResultMessage;
    f64               mElapsedMs;

    static TestResult Pass() { return { TestResultEnum::Pass, {}, 0.0 }; };
};

} // namespace harmony

#define TEST_ASSERT(cond, message, ...)                                        \
  if (!(cond)) {                                                               \
    HNY_LOG_ERROR(message, __VA_ARGS__);                                       \
    return TestResult { harmony::TestResultEnum::Fail, ##message, 0.0};        \
  }                                                                            \


#define TEST_APP_BEGIN_SUITE(suite_name)                            \
HARMONY_OVERRIDE_GLOBAL_NEW(true)                                  \
int main() {                                                        \
TestHashMap<TestString, harmony::TestResult> sResults{};         \
TestString sCurrentTestName = "";                                   \
HNY_LOG_INFO("%s Tests\n", suite_name);                             \


#define TEST_APP_END_SUITE() for(auto [name, result] : sResults) {\
    HNY_LOG_INFO("Test %s, Result : %s, Time Taken : %f ms\n", name.c_str(), result.mResult == harmony::TestResultEnum::Fail ? "Fail" : "Pass", result.mElapsedMs);\
    if(result.mResult != harmony::TestResultEnum::Pass) { HNY_LOG_INFO("    Test Message : %s\n", result.mResultMessage.c_str());}\
}};

#define ADD_TEST(TEST_NAME) {\
harmony::Engine e = harmony::Engine::Init(1280, 720, false, MEGABYTES(512), false);\
harmony::Timer timer_##TEST_NAME;\
auto result_##TEST_NAME = TEST_NAME(&e);\
f64 time_taken_##TEST_NAME = timer_##TEST_NAME.ElapsedMillisecondsF();\
result_##TEST_NAME.mElapsedMs = time_taken_##TEST_NAME;\
sResults[#TEST_NAME] = result_##TEST_NAME;}
