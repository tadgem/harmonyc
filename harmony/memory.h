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
	/// Given a size, begin address & end address
	/// allow allocation of any given type, 
	/// reusing previously freed locations
	/// </summary>
	struct FixedRangeAllocator
	{
		const uint64	mSize;
		const void*		mBegin;
		const void*		mEnd;
		
		void*			mHead = 0;
	};

	/// <summary>
	/// Global struct creating memory and 
	/// allowing creation of sub allocators for specific use cases
	/// </summary>
	struct Memory
	{
		uint64		mAllocatedBytes;
		uint8*		mMemory;

		template<uint64 MemorySize>
		static	Memory		Create()
		{
			return Memory
			{
				MemorySize, static_cast<uint8*>(mi_malloc(MemorySize))
			};
		}
	};
}
