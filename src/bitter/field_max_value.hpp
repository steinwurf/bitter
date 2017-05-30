// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include "field_mask.hpp"

#include <cstdint>
#include <cassert>

namespace bitter
{
/// @brief Function computing the max value fo a field.
template<class DataType, uint32_t Index, uint32_t... Sizes>
DataType field_max_value()
{
    // Note the max value is simply the numeric value of the bitmask
    return field_mask<DataType, Index, Sizes...>();
}
}
