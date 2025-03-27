#include "Engine.h"
#define FLECS_USE_OS_ALLOC
#include "flecs.h"
#include "mimalloc.h"

void* flecs_mi_malloc(int32 s)
{
	void* ptr = mi_malloc(s);
	return ptr;
}

void* flecs_mi_calloc(ecs_size_t s)
{
	void* ptr = mi_calloc(1, s);
	return ptr;
}

void* flecs_mi_realloc(void* p, int32 s)
{
	void* ptr = mi_realloc(p, s);
	return ptr;
}

void flecs_mi_free(void* p)
{
	mi_free(p);
}

namespace harmony
{
	void InitFlecsCustomAllocator()
	{
		ecs_os_set_api_defaults();

		ecs_os_api_t api = ecs_os_api;
		api.malloc_		= reinterpret_cast<ecs_os_api_malloc_t>(flecs_mi_malloc);
		api.calloc_		= reinterpret_cast<ecs_os_api_calloc_t>(flecs_mi_calloc);
		api.realloc_	= reinterpret_cast<ecs_os_api_realloc_t>(flecs_mi_realloc);
		api.free_		= reinterpret_cast<ecs_os_api_free_t>(flecs_mi_free);

		ecs_os_set_api(&api);
	}

	Engine Engine::Init(uint32 w, uint32 h, bool enableMSAA, uint64 upfrontMemory)
	{
		Memory mem = Memory::Create(upfrontMemory);

		// pass mimalloc functions so SDL uses the same memory space.
		SDL_SetMemoryFunctions(
			mi_malloc, mi_calloc, mi_realloc, mi_free
		);

		lvk::VkState vk = lvk::init::Create<lvk::VkSDL>("Harmony Engine", w, h, enableMSAA);
		lvk::LvkIm3dState im3d = lvk::LoadIm3D(vk);

		InitFlecsCustomAllocator();

		return Engine{ std::move(vk), std::move(mem), im3d, enableMSAA };
	}

	bool Engine::ShouldRun()
	{
		return mVK.m_Backend->ShouldRun(mVK);
	}

	void Engine::PreFrame()
	{
		mVK.m_Backend->PreFrame(mVK);
		Im3d::NewFrame();
	}

	void Engine::EndFrame()
	{
		Im3d::EndFrame();
		mVK.m_Backend->PostFrame(mVK);
	}
}