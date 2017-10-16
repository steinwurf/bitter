// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include "size_in_bits.hpp"
#include "lsb0.hpp"
#include "msb0.hpp"
#include "sum_sizes.hpp"
#include "field_size_in_bits.hpp"
#include "field_set.hpp"
#include "types.hpp"

#include <cstdint>
#include <cassert>

namespace bitter
{
/// @brief Writer class used for writing data to
/// the fields given in the variadic template Sizes
template
<
    typename DataType,
    typename BitNumbering,
    uint32_t... Sizes
>
class writer
{
public:

    /// Constructor
    writer()
    {
        static_assert(size_in_bits<DataType>() ==
                      sum_sizes<Sizes...>(),
                      "The size of the DataType in bits must exactly match the "
                      "sum of all the bit fields. If needed an unused bit "
                      "field can be added.");
    }

    /// @brief based on the provided index, the value is written
    /// @param value is the data, wished to written to the field at Index
    template<uint32_t Index>
    void field(typename DataType::type value)
    {
        static_assert(field_size_in_bits<Index, Sizes...>() <=
                      size_in_bits<DataType>(), "The field size in bits cannot "
                      "be larger than the total size of the data type");

        m_data = field_set<
                 DataType, BitNumbering, Index, Sizes...>(m_data, value);
    }

    /// @return The value create by the writer containing the bit fields
    typename DataType::type data() const
    {
        return m_data;
    }

private:

    /// The value built by the writer containing the different fields
    typename DataType::type m_data = 0;
};
}
