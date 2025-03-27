#include <cstdio>

#include "EASTL/allocator_malloc.h"
#include "EASTL/vector.h"

#include "lvk/lvk.h"

#include "STL.h"
#include "Macros.h"
#include "Engine.h"
#include "Memory.h"
#include "Assets.h"
#include "VkTech.h"

#define FLECS_USE_OS_ALLOC
#include "flecs.h"
#include "flecs/addons/cpp/flecs.hpp"
#include "harmony_unity.cpp"

HARMONY_OVERRIDE_GLOBAL_NEW(true)


template <typename T> using Vector = eastl::vector<T, eastl::allocator_malloc>;

void OnImGui(harmony::Engine& e)
{
    if (ImGui::Begin("Hello world!"))
    {

    }
    ImGui::End();
}

int main() {
  using namespace eastl;
  using namespace harmony;

  
  
  Engine engine = Engine::Init();

  AssetHandle sh{};
  String someString = "Hello";


  flecs::world ecs{};
  flecs::entity e = ecs.entity();
  e.insert([](glm::vec3 position)
  {
      position = { 1,2,3 };
  });



  while (engine.ShouldRun())
  {
      engine.PreFrame();

      OnImGui(engine);

      // Game Loop
      lvk::commands::RecordGraphicsCommands(engine.mVK, [&](VkCommandBuffer& cmd, uint32 frame) 
      {
            lvk::Array<VkClearValue, 2> clearValues{};
            clearValues[0].color = { {0.0f, 0.0f, 0.0f, 1.0f} };
            clearValues[1].depthStencil = { 1.0f, 0 };
            VkTech::ClearRenderPass(engine.mVK, cmd, frame, 
                engine.mVK.m_SwapchainImageRenderPass, engine.mVK.m_SwapChainFramebuffers[frame], engine.mVK.m_SwapChainImageExtent, clearValues);

      });

      engine.EndFrame();
  }
  return 0;
}
