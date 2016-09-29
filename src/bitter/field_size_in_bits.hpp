// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include <cstdint>

namespace bitter
{
/// @breif Function for getting the size of field in bits,
///        based on index given.
///
/// The algorithm takes an index and a variable list of sizes. To find the size
/// at e.g. index = 2 we loop over the list dropping the head of the list each
/// time index isn't zero. Once index == 0 we have foudn the size we are looking
/// for.
template<uint32_t Index, uint32_t Size0>
constexpr uint32_t field_size_in_bits()
{
    static_assert(Index == 0, "If there is only one size left. Then we "
                  "must be at index zero");
    return Size0;
}

template<uint32_t Index, uint32_t Size0, uint32_t Size1, uint32_t... Sizes>
constexpr uint32_t field_size_in_bits()
{
    // If Index is non zero call the field_size_in_bits(...) function otherwise
    // we have found the size we are looking for and we return that.
    return Index ? field_size_in_bits<Index - (Index ? 1 : 0),
           Size1, Sizes...>() : Size0;
}
}
