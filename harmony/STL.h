#pragma once

#include "Memory.h"
#include "EASTL/string.h"
#include "EASTL/unique_ptr.h"

namespace harmony
{
	typedef eastl::basic_string<char, mimalloc_allocator> String;
	
	template<typename _Ty>
	using Unique = eastl::unique_ptr<_Ty>;

	template<typename _Ty, typename... Args>
	Unique<_Ty>	MakeUnique(Args && ... args)
	{
		void* memory_loc = mi_malloc(sizeof(_Ty));
		Unique<_Ty> ptr = Unique<_Ty>(new (memory_loc) _Ty (eastl::forward<Args>(args)...));
		return ptr;
	}

	str_hash HashString(const String& input);
}