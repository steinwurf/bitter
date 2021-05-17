// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include "detail/bit_field.hpp"
#include "detail/field_get.hpp"
#include "detail/field_size_in_bits.hpp"
#include "detail/size_in_bits.hpp"
#include "detail/sum_sizes.hpp"
#include "detail/to_type.hpp"

#include "lsb0.hpp"
#include "msb0.hpp"
#include "types.hpp"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <typeinfo>
#include <vector>

namespace bitter
{
/// @brief Reader class used for reading the content
///        of the value parsed to the reader at initialization
template <typename Type, typename BitNumbering, std::size_t... Sizes>
class reader
{
public:
    // Get the bitter type
    using bitter_type = to_type<Type>;

    /// Small alias for the bit_field
    template <std::size_t Index>
    using bit_field_type = bit_field<typename bitter_type::type,
                                     field_size_in_bits<Index, Sizes...>()>;

    /// @brief Reader constructor
    /// DataType must be either u8, u16, u24, u32, u40, u48, u56, or u64
    reader(typename bitter_type::type value) : m_value(value)
    {
        static_assert(size_in_bits<bitter_type>() == sum_sizes<Sizes...>(),
                      "size of the DataType is not equal to the sum of sizes");
    }

    /// @brief Based on the provided index the function returns the field
    template <std::size_t Index>
    bit_field_type<Index> field() const
    {
        return bit_field_type<Index>(get<Index>());
    }

private:
    /// @brief Function used as a wrapper, used for retrieving a field
    ///        based on the Index provide
    template <std::size_t Index>
    typename bitter_type::type get() const
    {
        return field_get<bitter_type, BitNumbering, Index, Sizes...>(m_value);
    }

private:
    /// Store the value containing the data used by the reader
    typename bitter_type::type m_value;
};
}
