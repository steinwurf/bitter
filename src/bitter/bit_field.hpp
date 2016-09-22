// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include "size_in_bits.hpp"

#include <type_traits>
#include <cstdint>
#include <cassert>

namespace bitter
{
template<typename DataType>
class bit_field
{
public:
    bit_field(DataType value, uint32_t size) :
        m_value(value),
        m_size(size)
    {

    }

    // Return value as the requested type
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

private:
    DataType m_value;
    uint32_t m_size;
};
}
