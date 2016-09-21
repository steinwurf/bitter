// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include <cstdint>

namespace bitter
{
template<uint32_t Index, uint32_t Size0>
uint32_t field_offset()
{
    static_assert(Index == 0, "");
    return 0;
}

template<uint32_t Index, uint32_t Size0, uint32_t Size1, uint32_t... Sizes>
uint32_t field_offset()
{
    if (Index == 0)
    {
        return 0;
    }
    else
    {
        return Size0 +
               field_offset<Index - (Index ? 1 : 0), Size1, Sizes...>();
    }
}
}
