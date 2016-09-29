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
/// @brief Small class used for wrapping a bitfield
/// @param value is the value of the bit we are wrapping
/// @param size is the size of the field in bits
template<typename DataType, uint32_t Size>
class bit_field
{

public:
    bit_field(DataType value) :
        m_value(value)
    {
        static_assert(Size > 0, "Size is less than or equal to 0");
    }


    /// @return m_value cast to the type of ReturnType
    template<typename ReturnType>
    ReturnType read_as()
    {
        // Check if the field fits into the size of ReturnType
        assert(sizeof(ReturnType) <= sizeof(DataType));

        // Check if the size provide can fit into ReturnType
        assert(Size <= size_in_bits<ReturnType>());

        return (ReturnType) m_value;

    }

private:
    DataType m_value;
};
}
