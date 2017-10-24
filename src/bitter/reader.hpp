// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include "size_in_bits.hpp"
#include "sum_sizes.hpp"
#include "field_get.hpp"
#include "field_size_in_bits.hpp"
#include "lsb0.hpp"
#include "msb0.hpp"
#include "bit_field.hpp"
#include "types.hpp"

#include <cstdint>
#include <vector>
#include <cassert>
#include <typeinfo>

namespace bitter
{
/// @brief Reader class used for reading the content
///        of the value parsed to the reader at initialization
template<typename DataType, typename BitNumbering, uint32_t... Sizes>
class reader
{
public:

    /// Small alias for the bit_field
    template<uint32_t Index>
    using bit_field_type =
        bit_field<typename DataType::type, field_size_in_bits<Index, Sizes...>()>;

    /// @brief Reader constructor
    /// DataType must be either uint8_t, uint16_t, uint32_t, or uint64_t
    reader(typename DataType::type value) :
        m_value(value)
    {
        static_assert(size_in_bits<DataType>() == sum_sizes<Sizes...>(),
                      "size of the DataType is not equal to the sum of sizes");
    }

    /// @brief Based on the provided index the function returns the field
    template<uint32_t Index>
    bit_field_type<Index> field() const
    {
        return bit_field_type<Index>(get<Index>());
    }

private:
    /// @brief Function used as a wrapper, used for retrieving a field
    ///        based on the Index provide
    template<uint32_t Index>
    typename DataType::type get() const
    {
        return field_get<DataType, BitNumbering, Index, Sizes...>(m_value);
    }

private:

    /// Store the value containing the data used by the reader
    typename DataType::type m_value;
};
}
