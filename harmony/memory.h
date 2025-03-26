#pragma once
#include "primitives.h"
#include "mimalloc.h"

/// <summary>
/// Macro to globally override new
/// Used to track non-allocator'd code
/// while still use the upfront page we create for the engine
/// </summary>
#define HARMONY_OVERRIDE_GLOBAL_NEW(ENABLE_PRINT)\
void *__cdecl operator new[](size_t size, const char *name, int flags,\
unsigned debugFlags, const char* file, int line) {\
	ENABLE_PRINT ? printf("Unassigned Allocation!\n") : 0;\
	return mi_malloc(size);\
}\
\
void* __cdecl operator new[](size_t size, unsigned __int64, unsigned __int64,\
	char const*, int, unsigned int, char const*,\
	int) {\
	ENABLE_PRINT ? printf("Unassigned Allocation!\n") : 0;\
	return mi_malloc(size);\
}

namespace harmony
{
	/// <summary>
	/// Global struct creating memory and 
	/// allowing creation of sub allocators for specific use cases
	/// </summary>
	struct Memory
	{
		uint64			mAllocatedBytes;
		void*			mMemory;
		mi_arena_id_t	mArenaId;
		mi_heap_t*		mHeap;

		template<uint64 MemorySize>
		static	Memory		Create()
		{
			void* memory = std::malloc(MemorySize);
			mi_option_set(mi_option_show_errors, 1);
			mi_option_set(mi_option_verbose, 1);
			mi_arena_id_t arenaId;
			constexpr bool is_committed = true;
			constexpr bool is_large = true;
			constexpr bool is_exclusive = true;
			constexpr bool is_zeroed = false;
			constexpr int  numa_mode = -1;
			mi_manage_os_memory_ex(memory, MemorySize, 
				is_committed, is_large, is_zeroed, 
				numa_mode, is_exclusive, &arenaId);

			mi_heap_t* engineHeap = mi_heap_new_in_arena(arenaId);
			mi_heap_set_default(engineHeap);

			return Memory
			{
				MemorySize,
				memory,
				arenaId,
				engineHeap
			};
		}
	};
}
