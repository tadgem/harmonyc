#pragma once
#include "Macros.h"
#include "Memory.h"
#include "Primitives.h"
#include "VkSDL.h"
#include "VkTech.h"
namespace harmony {
class Engine {
public:
  lvk::VkState mVK;
  Memory mMemory;
  lvk::LvkIm3dState mIm3D;
  bool mEnableMSAA = false;

  static Engine Init(uint32 swapchainWidth = 1920,
                     uint32 swapchainHeight = 1080, bool enableMSAA = false,
                     uint64 upfrontMemory = GIGABYTES(4));

  bool ShouldRun();
  void PreFrame();
  void EndFrame();
};
} // namespace harmony
