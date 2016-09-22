// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include "field_mask.hpp"
#include "field_offset.hpp"

#include <cstdint>
#include <cassert>

namespace bitter
{
    template<class DataType, uint32_t Index, uint32_t... Sizes>
    DataType field_set(DataType value, DataType field)
    {
        uint32_t offset = field_offset<Index, Sizes...>();
        DataType mask = field_mask<DataType, Index, Sizes...>();

        // Sanity check that we don't have garbage bits in our field
        assert((field & (~mask)) == 0U);

        // Shift the field up to where it should go
        // and do the same with the mask
        field = field << offset;
        mask = mask << offset;

        /// Merge the bits:
        /// https://graphics.stanford.edu/~seander/bithacks.html#MaskedMerge
        value = value ^ ((value ^ field) & mask);

        return value;
    }
}
