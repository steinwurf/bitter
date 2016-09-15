// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include "field_offset.hpp"
#include "field_mask.hpp"


#include <cstdint>
#include <cassert>

namespace bitter
{
    template<class DataType, uint32_t Index, uint32_t... Sizes>
    DataType field_get(DataType value)
    {
        uint32_t offset = field_offset<Index, Sizes...>();
        DataType mask = field_mask<DataType, Index, Sizes...>();

        return (value >> offset) & mask;
    }
}
