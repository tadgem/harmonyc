#pragma once

#include "json.hpp"
#include "STL.h"

namespace harmony
{

    // TODO: Get rid of STL here,
    // this doesnt work because the eastl vector class
    // does not accept the same kind of allocator expected
    // by the std::vector class (e.g. std expects allocator<InnerElemType>
    // eastl just expects a non-templalte allocator. 
    // _should_ mostly be fine sans speed 
    // as we are using the mimalloc allocator, so will be within our 
    // pre-allocated memory space.
    using Json = nlohmann::basic_json <
        std::map,
        std::vector,
        String,
        bool,
        int64,
        uint64,
        f64,
        STLMimallocAllocator,
        nlohmann::adl_serializer,
        std::vector<uint8>,
        void>;
}