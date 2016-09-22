// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include "size_in_bits.hpp"
#include "sum_sizes.hpp"
#include "field_set.hpp"

#include <cstdint>
#include <cassert>
#include <type_traits>

namespace bitter
{
template<class DataType, uint32_t... Sizes>
struct writer
{
    writer()
    {
        static_assert(size_in_bits<DataType>() ==
                      sum_sizes<Sizes...>(), "stop it..");
    }

    template<uint32_t Index>
    void field(DataType value)
    {
        m_data = field_set<DataType, Index, Sizes...>(m_data, value);
    }

    DataType data() const
    {
        return m_data;
    }

    DataType m_data = 0;
};
}
