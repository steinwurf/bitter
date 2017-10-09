// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include <cstdint>
#include <type_traits>

#include "lsb0.hpp"
#include "msb0.hpp"
#include "size_in_bits.hpp"
#include "field_offset.hpp"

namespace bitter
{

template<class DataType, uint32_t Index, uint32_t... Sizes>
uint32_t endian_field_offset(lsb0)
{
    return field_offset<Index, Sizes...>();
}

template<class DataType, uint32_t Index, uint32_t... Sizes>
uint32_t endian_field_offset(msb0)
{
    uint32_t offset = field_offset<Index, Sizes...>();

    return size_in_bits<DataType>() - 1 - offset;
}


}
