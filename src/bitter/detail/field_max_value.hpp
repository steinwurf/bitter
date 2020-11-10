// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include "field_mask.hpp"

#include <cstddef>
#include <cstdint>

namespace bitter
{
/// @brief Function computing the max value for a field.
template<class DataType, std::size_t Index, std::size_t... Sizes>
constexpr typename DataType::type field_max_value()
{
    // Note the max value is simply the numeric value of the bitmask
    return field_mask<DataType, Index, Sizes...>();
}
}
