#pragma once
#include "primitives.h"
#include "vk_tech.h"
#include "VkSDL.h"

namespace harmony
{
	class Engine
	{
	public:
		lvk::VkState		mVK;
		lvk::LvkIm3dState	mIm3D;
		bool				mEnableMSAA = false;

		static Engine Init(uint32 swapchainWidth = 1920, uint32 swapchainHeight = 1080, bool enableMSAA = false);

		bool ShouldRun();
		void PreFrame();
		void EndFrame();

	};
}