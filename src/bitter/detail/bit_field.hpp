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
/// @brief Small class used for wrapping a single bit field and allow it to be
/// read in a convenient way.
template<typename DataType, uint32_t Size>
class bit_field
{
public:

    /// Constructor
    /// @param value is the value of the bit we are wrapping
    bit_field(DataType value) :
        m_value(value)
    {
        static_assert(Size > 0, "A bit field cannot have a size of zero bits");
    }

    /// @return The bit field value cast to the type of ReturnType
    template<typename ReturnType>
    ReturnType as() const
    {
        // Check if the size provide can fit into ReturnType
        static_assert(Size <= size_in_bits<ReturnType>(), "There are not "
                      "enough bits in ReturnType to represent this bit field");

        return (ReturnType) m_value;
    }

private:

    /// The value representing this bitfield
    DataType m_value;
};
}
