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

struct TestCandidate {
  TestString mName;
  TestResult (*mTestFunc)(Engine *e);
};

} // namespace harmony

static void TestGUI(harmony::TestVector<harmony::TestCandidate> &tests,
                    harmony::TestVector<harmony::TestResult> &results) {

  harmony::Engine e =
      harmony::Engine::Init(1600, 900, false, MEGABYTES(512), false);

  while (e.ShouldRun()) {
    e.PreFrame();

    // do test imgui
    if (ImGui::Begin("Test Explorer")) {
      for (auto &test : tests) {
        if (ImGui::Button(test.mName.c_str())) {
          // enqueue test and shutdown test explorer app
          HNY_LOG_ERROR("Running Test : %s\n", test.mName.c_str());
        }
      }
    }
    ImGui::End();

    lvk::commands::RecordGraphicsCommands(
        *e.mVK, [&](VkCommandBuffer &cmd, uint32 frame) {
          lvk::Array<VkClearValue, 2> clearValues{};
          clearValues[0].color = {{0.0f, 0.0f, 0.0f, 1.0f}};
          clearValues[1].depthStencil = {1.0f, 0};
          harmony::VkTech::ClearRenderPass(
              *e.mVK, cmd, frame, e.mVK->m_SwapchainImageRenderPass,
              e.mVK->m_SwapChainFramebuffers[frame],
              e.mVK->m_SwapChainImageExtent, clearValues);
        });

    e.EndFrame();
  }
  // spin up imgui instance,
  // allow user to pick one test or run all (custom config TODO)
  //
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
    TestVector<harmony::TestCandidate> sTests{};                               \
    TestString sCurrentTestName = "";                                          \
    HNY_LOG_INFO("%s Tests\n", suite_name);

#define TEST_APP_END_SUITE()                                                   \
  TestGUI(sTests, sResults);                                                   \
  }
;

#define ADD_TEST(TEST_NAME)                                                    \
  {                                                                            \
    sTests.push_back({#TEST_NAME, &TEST_NAME});                                \
  }
