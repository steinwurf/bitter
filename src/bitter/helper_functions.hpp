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
    uint32_t field_size()
    {
        static_assert (Index == 0, "");
        return Size0;
    }

    template<uint32_t Index, uint32_t Size0, uint32_t Size1, uint32_t... Sizes>
    uint32_t field_size()
    {
        if (Index == 0)
        {
            return Size0;
        }
        else
        {
            return field_size<Index - (Index ? 1 : 0), Size1, Sizes...>();
        }
    }

    template<uint32_t Index, uint32_t... Sizes>
    uint32_t field_mask()
    {
        /// http://stackoverflow.com/a/1392065/1717320
        return (1 << field_size<Index, Sizes...>()) - 1;
    }

    template<class DataType, uint32_t Index, uint32_t... Sizes>
    DataType field_set(DataType value, DataType field)
    {
        uint32_t offset = field_offset<Index, Sizes...>();
        uint32_t mask = field_mask<Index, Sizes...>();

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
        uint32_t mask = field_mask<Index, Sizes...>();

        return (value >> offset) & mask;
    }

    // template<uint32_t Group, uint32_t NextGroup, uint32_t... RemainingGroups>
    // uint32_t total_size_of_groups_()
    // {
    //     return Group + total_size_of_groups_<NextGroup, RemainingGroups...>();
    // }

    // template<uint32_t Group>
    // uint32_t total_size_of_groups_()
    // {
    //     return Group;
    // }
}
