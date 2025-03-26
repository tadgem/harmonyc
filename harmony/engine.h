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

		static Engine Init(uint32 swapchainWidth = 1920, uint32 swapchainHeight = 1080, bool enableMSAA = false)
		{
			lvk::VkState vk = lvk::init::Create<lvk::VkSDL>("Harmony Engine", swapchainWidth, swapchainHeight, enableMSAA);
			lvk::LvkIm3dState im3d = lvk::LoadIm3D(vk);

			return Engine{ std::move(vk), im3d, enableMSAA };
		}

		bool ShouldRun()
		{
			return mVK.m_Backend->ShouldRun(mVK);
		}

		void PreFrame()
		{
			mVK.m_Backend->PreFrame(mVK);
			Im3d::NewFrame();
		}

		void EndFrame()
		{
			Im3d::EndFrame();
			mVK.m_Backend->PostFrame(mVK);
		}

	};
}