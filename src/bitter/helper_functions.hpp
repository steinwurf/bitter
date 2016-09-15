// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include <cstdint>
#include <cassert>
namespace bitter
{
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

    template<uint32_t Size0>
    constexpr uint32_t sum_sizes()
    {
        return Size0;
    }

    template<uint32_t Size0, uint32_t Size1, uint32_t... Sizes>
    constexpr uint32_t sum_sizes()
    {
        return Size0 + sum_sizes<Size1, Sizes...>();
    }

    template<uint32_t Index, uint32_t Size0>
    uint32_t field_offset()
    {
        static_assert (Index == 0, "");
        return 0;
    }

    template<uint32_t Index, uint32_t Size0, uint32_t Size1, uint32_t... Sizes>
    uint32_t field_offset()
    {
        if (Index == 0)
        {
            return 0;
        }
        else
        {
            return Size0 +
                field_offset<Index - (Index ? 1 : 0), Size1, Sizes...>();
        }
    }

    template<uint32_t Index, uint32_t Size0>
    uint32_t field_size_in_bits()
    {
        static_assert (Index == 0, "");
        return Size0;
    }

    template<uint32_t Index, uint32_t Size0, uint32_t Size1, uint32_t... Sizes>
    uint32_t field_size_in_bits()
    {
        if (Index == 0)
        {
            return Size0;
        }
        else
        {
            return field_size_in_bits<Index - (Index ? 1 : 0), Size1, Sizes...>();
        }
    }

    template<class DataType, uint32_t Index, uint32_t... Sizes>
    DataType field_mask()
    {
        uint32_t field_size = field_size_in_bits<Index, Sizes...>();
        uint32_t data_type_size = size_in_bits<DataType>();

        assert(field_size <= data_type_size);

        if (field_size == data_type_size)
        {
            // If the field size (in bits) is equal to the size of the DataType in
            // bits. Then the below calculation does not work (we will shift over
            // the end of the data type). Instead we just need to create an all ones
            // mask.
            DataType mask = 0;
            return ~0;
        }
        else
        {
            // http://stackoverflow.com/a/1392065/1717320
            DataType mask = 1;
            return (mask << field_size) - 1;
        }

    }

    template<class DataType, uint32_t Index, uint32_t... Sizes>
    DataType field_set(DataType value, DataType field)
    {
        uint32_t offset = field_offset<Index, Sizes...>();
        DataType mask = field_mask<DataType, Index, Sizes...>();

        // Sanity check that we don't have garbage bits in our field
        assert((field & (~mask)) == 0U);

        // Shift the field up to where it should go and do the same with the mask
        field = field << offset;
        mask = mask << offset;

        /// Merge the bits:
        /// https://graphics.stanford.edu/~seander/bithacks.html#MaskedMerge
        value = value ^ ((value ^ field) & mask);

        return value;
    }

    template<class DataType, uint32_t Index, uint32_t... Sizes>
    DataType field_get(DataType value)
    {
        uint32_t offset = field_offset<Index, Sizes...>();
        DataType mask = field_mask<DataType, Index, Sizes...>();

        return (value >> offset) & mask;
    }
}
