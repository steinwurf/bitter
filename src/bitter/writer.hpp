// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include "size_in_bits.hpp"

#include "sum_sizes.hpp"
#include "field_size_in_bits.hpp"
#include "field_set.hpp"

#include <cstdint>
#include <cassert>

namespace bitter
{
/// @brief Writer class used for writing data to
/// the fields given in the variadic template Sizes
template<class DataType, uint32_t... Sizes>
class writer
{
public:
    writer()
    {
        static_assert(size_in_bits<DataType>() ==
                      sum_sizes<Sizes...>(),
                      "size of the Datatype is not equal to the sum of sizes");
    }

    /// @prief based on the provided index, the value is written
    /// @param value is the data, wished to written to the field at Index
    template<uint32_t Index>
    void field(DataType value)
    {
        assert((field_size_in_bits<Index, Sizes...>() <=
                size_in_bits<DataType>()));

        m_data = field_set<DataType, Index, Sizes...>(m_data, value);
    }

    DataType data() const
    {
        return m_data;
    }

private:

    DataType m_data = 0;
};
}
