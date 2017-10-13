// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include <cassert>
#include <cstdint>
#include <type_traits>

#include "field_mask.hpp"
#include "field_max_value.hpp"

namespace bitter
{

/// @brief set the value in a bitfield based on the index
/// @param bitfield is the data of the writer
/// @param value is the data we want to write to the bitfield
template
<
    typename DataType,
    typename BitNumbering,
    uint32_t Index,
    uint32_t... Sizes
>
DataType field_set(DataType bitfield, DataType value)
{
    // Verify that the bitfield can be represented with the available bits:
    assert((value <= field_max_value<DataType, Index, Sizes...>()) &&
           "value exceeds limit representable by available bits");

    uint32_t offset = BitNumbering::template field_offset<Index, Sizes...>();
    DataType mask = field_mask<DataType, Index, Sizes...>();

    // Shift the value up to where it should go
    // and do the same with the mask
    value = value << offset;
    mask = mask << offset;

    // Merge the bits:
    // https://graphics.stanford.edu/~seander/bithacks.html#MaskedMerge
    bitfield = bitfield ^ ((bitfield ^ value) & mask);

    return bitfield;
}
}
