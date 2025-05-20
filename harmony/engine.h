#pragma once
#include "AssetManager.h"
#include "Macros.h"
#include "Memory.h"
#include "Primitives.h"
#include "VkSDL.h"
#include "VkTech.h"

namespace harmony {
class Engine {
public:
  Memory mMemory;
  Unique<AssetManager> mAssetManager;
  Unique<lvk::VkState> mVK;
  Unique<lvk::LvkIm3dState> mIm3D;
  bool mEnableMSAA = false;

  static Engine Init(uint32 swapchainWidth = 1920,
                     uint32 swapchainHeight = 1080, bool enableMSAA = false,
                     uint64 upfrontMemory = GIGABYTES(4),
                     bool enableValidation = true);

  bool ShouldRun() const;
  void PreFrame() const;
  void EndFrame() const;
  void Shutdown();

  ~Engine() { Shutdown(); }
};
} // namespace harmony
