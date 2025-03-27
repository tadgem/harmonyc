#pragma once

#include "Memory.h"
#include "EASTL/string.h"

namespace harmony
{
	typedef eastl::basic_string<char, mimalloc_allocator> String;

	str_hash HashString(const String& input);
}