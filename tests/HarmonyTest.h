#pragma once
#include <cstdio>
#define FLECS_USE_OS_ALLOC
#include "Assets.h"
#include "ECS.h"
#include "Engine.h"
#include "Json.h"
#include "Macros.h"
#include "Maths.h"
#include "Memory.h"
#include "STL.h"
#include "Timer.h"
#include "Utils.h"
#include "VkTech.h"
#include "flecs.h"
#include "flecs/addons/cpp/flecs.hpp"
#include "lvk/lvk.h"

namespace harmony {
enum class TestResultEnum { Fail = -1, Pass = 0, DNF = 1 };

using TestString =
    std::basic_string<char, std::char_traits<char>, std::allocator<char>>;

template <typename _Value>
using TestVector = std::vector<_Value, std::allocator<_Value>>;

struct TestResult {
  TestString mName;
  TestResultEnum mResult;
  TestString mResultMessage;
  f64 mElapsedMs;

  static TestResult Pass() {
    return {"Unknown Test", TestResultEnum::Pass, {}, 0.0};
  };
};

} // namespace harmony

static void TestGUI() {

}

#define STRINGIZE_DETAIL(x) #x
#define STRINGIZE(x) STRINGIZE_DETAIL(x)
#define FLOATING_POINT_ROUGHLY_EQUAL(x, y) abs(abs(x) - abs(y)) <= 0.00001

#define TEST_ASSERT(cond, message, ...)                                        \
  if (!(cond)) {                                                               \
    return TestResult{"", harmony::TestResultEnum::Fail,                       \
                      ##message                                                \
                      " : Test failed at " __FILE__                            \
                      ", Line " STRINGIZE(__LINE__) " : " #cond, 0.0};         \
  }

#define TEST_APP_BEGIN_SUITE(suite_name, engine_heap_size)                     \
  HARMONY_OVERRIDE_GLOBAL_NEW(true)                                            \
  int main() {                                                                 \
    constexpr uint64 TEST_HEAP_SIZE = engine_heap_size;                        \
    TestVector<harmony::TestResult> sResults{};                                \
    TestString sCurrentTestName = "";                                          \
    HNY_LOG_INFO("%s Tests\n", suite_name);

#define TEST_APP_END_SUITE()                                                   \
  for (auto &result : sResults) {                                              \
    HNY_LOG_INFO("Test %s, Result : %s" NORMAL_PRINT_CODE                      \
                 ",Time Taken : %f ms\n",                                      \
                 result.mName.c_str(),                                         \
                 result.mResult == harmony::TestResultEnum::Fail               \
                     ? RED_PRINT_CODE "Fail"                                   \
                     : GREEN_PRINT_CODE "Pass",                                \
                 result.mElapsedMs);                                           \
    if (result.mResult != harmony::TestResultEnum::Pass) {                     \
      HNY_LOG_ERROR(" > Message : %s\n", result.mResultMessage.c_str());       \
    }                                                                          \
  }                                                                            \
  }                                                                            \
  ;

#define ADD_TEST(TEST_NAME)                                                    \
  {                                                                            \
    HNY_LOG_INFO("Running Test : %s\n", #TEST_NAME);                           \
    harmony::Engine e =                                                        \
        harmony::Engine::Init(1280, 720, false, TEST_HEAP_SIZE, false);        \
    harmony::Timer timer_##TEST_NAME;                                          \
    auto result_##TEST_NAME = TEST_NAME(&e);                                   \
    result_##TEST_NAME.mName = #TEST_NAME;                                     \
    f64 time_taken_##TEST_NAME = timer_##TEST_NAME.ElapsedMillisecondsF();     \
    result_##TEST_NAME.mElapsedMs = time_taken_##TEST_NAME;                    \
    sResults.push_back(result_##TEST_NAME);                                    \
  }
