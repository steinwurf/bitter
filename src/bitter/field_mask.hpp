// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include "field_size_in_bits.hpp"

#include <cstdint>
#include <cassert>

namespace bitter
{
    template<class DataType, uint32_t Index, uint32_t... Sizes>
    DataType field_mask()
    {
        uint32_t field_size = field_size_in_bits<Index, Sizes...>();
        uint32_t data_type_size = size_in_bits<DataType>();

        assert(field_size <= data_type_size);

        if (field_size == data_type_size)
        {
            // If the field size (in bits) is equal to the size of the DataType
            // in bits. Then the below calculation does not work (we will shift
            // over the end of the data type). Instead we just need to create an
            // all ones mask.
            DataType mask = 0;
            return ~mask;
        }
        else
        {
            // http://stackoverflow.com/a/1392065/1717320
            DataType mask = 1;
            return (mask << field_size) - 1;
        }

    }

}
