// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include <cstdint>

namespace bitter
{
/// @breif function for getting the size of DataType in bits
template<class DataType>
constexpr uint32_t size_in_bits()
{
    return sizeof(DataType)*8;
}

template<>
constexpr uint32_t size_in_bits<bool>()
{
    return 1U;
}
}
