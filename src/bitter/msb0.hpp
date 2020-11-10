// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include <cstddef>
#include <cstdint>

#include "detail/sum_sizes.hpp"

namespace bitter
{
/// @brief Calculates the bit shift offset into a value given that bitter
///        is configured in MSB 0 numbering mode (see README.rst for more
///        information).
struct msb0
{
    /// The basic implementation in MSB 0 mode works according to the
    /// following observation.
    ///
    /// If we want to access a given field at index X then we need to
    /// shift right past the fields at X+1, X+2, ... etc.
    ///
    /// Example:
    ///
    /// field index: 0     1         2         3
    /// field size:  1     2         3         2
    /// bit index:   0   1   2   3   4   5   6   7
    ///            +---+-------+-----------+-------+
    ///            | 0 | 1   0 | 1   1   1 | 0   0 |
    ///            +---+-------+-----------+-------+
    ///              ^
    ///              |             most significant
    ///              +-----------+ bit
    ///
    /// Say we want to access field index 1, then we need to shift it
    /// right past field 2 and 3. They have size 3+2 = 5 bits.
    ///
    /// We do this by implementing a counter which iterates through the
    /// field sizes once we reach the index we are interested in we
    /// sum the remaining sizes.
    ///
    template<uint32_t Index, std::size_t... Sizes>
    static std::size_t field_offset()
    {
        return count_to_field_offset<Index, 0, Sizes...>();
    }

private:

    template
    <
        std::size_t Index,
        std::size_t Counter,
        std::size_t Size0
    >
    static std::size_t count_to_field_offset()
    {
        static_assert(Index == Counter, "");
        return 0;
    }

    template
    <
        std::size_t Index,
        std::size_t Counter,
        std::size_t Size0,
        std::size_t Size1,
        std::size_t... Sizes
    >
    static std::size_t count_to_field_offset()
    {
        if (Index == Counter)
        {
            return sum_sizes<Size1, Sizes...>();
        }
        else
        {
            return count_to_field_offset<
                   Index,
                   Counter + (Counter < Index ? 1 : 0),
                   Size1,
                   Sizes...>();
        }
    }
};
}
