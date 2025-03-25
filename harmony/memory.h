#pragma once
#include "primitives.h"
#include "mimalloc.h"
#include "EASTL/unordered_map.h"

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