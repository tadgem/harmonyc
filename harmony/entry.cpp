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
#include "Json.h"

#define FLECS_USE_OS_ALLOC
#include "flecs.h"
#include "flecs/addons/cpp/flecs.hpp"
#include "harmony_unity.cpp"

HARMONY_OVERRIDE_GLOBAL_NEW(true)



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
  SerializableAssetHandle handle(someString, AssetType::Audio);

  printf("Handle Str : %s\n", handle.mPath);
  {
      Unique<glm::vec3> someUniqueData = MakeUnique<glm::vec3>(10, 20, 30);
      AssetT<glm::vec3, AssetType::Audio> asset(someString, someUniqueData);
      AssetIntermediateT<glm::vec3, glm::vec3, AssetType::Audio> inter(static_cast<Asset*>(&asset), glm::vec3(0.0f));

      glm::vec3 result = *asset.mData;
  }

  flecs::world ecs{};
  flecs::entity e = ecs.entity();
  e.insert([](glm::vec3 position)
  {
      position = { 1,2,3 };
  });

  Json someJson;
  someJson["dad"] = 3;
  int64 val = someJson["dad"];

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
