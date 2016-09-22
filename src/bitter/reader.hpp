// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include "size_in_bits.hpp"
#include "sum_sizes.hpp"
#include "field_get.hpp"
#include "field_offset.hpp"
#include "field_size_in_bits.hpp"

#include "bit_field.hpp"

#include <cstdint>
#include <vector>
#include <cassert>
#include <typeinfo>

namespace bitter
{
template<typename DataType, uint32_t... Sizes>
class reader
{
public:
    reader(DataType value) :
        m_value(value)
    {
        static_assert(size_in_bits<DataType>() == sum_sizes<Sizes...>(),
                      "size of the Datatype is not equal to the sum of sizes");
    }

    // Based on the index given, the function returns the field
    template<uint32_t Index>
    bit_field<DataType> field()
    {
        auto size = field_size_in_bits<Index, Sizes...>();
        return bit_field<DataType>(read<Index>(), size);
    }

private:
    template<uint32_t Index>
    DataType read()
    {
        return field_get<DataType, Index, Sizes...>(m_value);
    }



private:
    DataType m_value;
};
}
