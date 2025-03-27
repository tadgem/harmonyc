#pragma once

#include "memory.h"
#include "EASTL/string.h"

namespace harmony
{
	typedef eastl::basic_string<char, mimalloc_allocator> String;
}