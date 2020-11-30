// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include "field_size_in_bits.hpp"
#include "size_in_bits.hpp"

#include <cassert>
#include <cstdint>

namespace bitter
{
/// @brief Function for creating a mask for a variable
///        with the size of DataType
template <class DataType, uint32_t Index, uint32_t... Sizes>
typename DataType::type field_mask()
{
    uint32_t field_size = field_size_in_bits<Index, Sizes...>();

    // The size of the field cannot exceed the number of bits allowed
    // in the data type
    assert(field_size <= size_in_bits<DataType>());

    if (field_size == size_in_bits<typename DataType::type>())
    {
        // If the field size (in bits) is equal to the size of the DataType
        // in bits. Then the below calculation does not work (we will shift
        // over the end of the data type). Instead we just need to create an
        // all ones mask.
        typename DataType::type mask = 0;
        return ~mask;
    }
    else
    {
        // http://stackoverflow.com/a/1392065/1717320
        typename DataType::type mask = 1;
        return (mask << field_size) - 1;
    }
}
}
