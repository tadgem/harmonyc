#include <cstdio>

#include "EASTL/allocator_malloc.h"
#include "EASTL/vector.h"

#include "lvk/lvk.h"

#include "macros.h"
#include "engine.h"
#include "memory.h"
#include "vk_tech.h"
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
  
  uint64 size = GIGABYTES(4);
  // TODO: Map some block of memory to mimalloc
  // Memory mem = Memory::Create<GIGABYTES(4)>();

  // pass mimalloc functions so SDL uses the same memory space.
  SDL_SetMemoryFunctions(
      mi_malloc, mi_calloc, mi_realloc, mi_free
  );

  Engine engine = Engine::Init();

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
