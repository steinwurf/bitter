// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include <cstdint>

namespace bitter
{
    /// @breif Function for getting the size of field in bits,
    ///        based on index given.
    template<uint32_t Index, uint32_t Size0>
    constexpr uint32_t field_size_in_bits()
    {
        static_assert (Index == 0, "");
        return Size0;
    }

    template<uint32_t Index, uint32_t Size0, uint32_t Size1, uint32_t... Sizes>
    constexpr uint32_t field_size_in_bits()
    {
        return Index ? field_size_in_bits<Index - (Index ? 1 : 0),
            Size1, Sizes...>() : Size0;
    }
}
