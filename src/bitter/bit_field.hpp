// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include "size_in_bits.hpp"

#include <type_traits>
#include <cstdint>

namespace bitter
{
template<typename DataType>
struct bit_field
{
    bit_field(DataType value, uint32_t size) :
        m_value(value),
        m_size(size)
    {

    }

    template<typename ReturnType>
    ReturnType read_as()
    {
        assert(sizeof(ReturnType) <= sizeof(DataType));
        assert(m_size <= size_in_bits<ReturnType>());
        if(std::is_same<bool, ReturnType>::value)
        {
            if(m_value == 0U)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        else
        {
            return (ReturnType) m_value;
        }
    }

    DataType m_value;
    uint32_t m_size;
};
}
