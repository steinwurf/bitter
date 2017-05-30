// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include <cassert>
#include <cmath>
#include <cstdint>
#include <type_traits>

#include "field_mask.hpp"
#include "field_offset.hpp"
#include "field_size_in_bits.hpp"

#include <iostream>

namespace bitter
{
namespace detail
{
template<typename T>
inline constexpr T pow2(const T exponent)
{
    return (exponent == 0) ? 1 : (2 * pow2(exponent - 1));
}
}

/// @brief set the value in a bitfield based on the index
/// @param bitfield is the data of the writer
/// @param value is the data we want to write to the bitfield
template<class DataType, uint32_t Index, uint32_t... Sizes>
DataType field_set(DataType bitfield, DataType value)
{
    using bitfield_limit =
        std::integral_constant<uint64_t,
        detail::pow2((uint64_t)field_size_in_bits<Index, Sizes...>())>;

    // Verify that the bitfield can be represented with the available bits:
    assert(value < bitfield_limit::value &&
           "value exceeds limit representable by available bits");

    uint32_t offset = field_offset<Index, Sizes...>();
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
