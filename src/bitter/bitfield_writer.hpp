// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once
#include "helper_functions.hpp"

#include <cstdint>
#include <cassert>
#include <type_traits>

#include <iostream>

namespace bitter
{
template<typename DataType, uint32_t... Groups>
class bitfield_writer
{
public:
    bitfield_writer():
        m_data(0)
    {

    }

    template<uint32_t Group, typename Type>
    void write(Type data)
    {

        auto size = group_size<Group>();
        auto offset = group_offset<Group>();

        if (std::is_same<Type, bool>() == true)
        {
            uint8_t value = 0U;
            if (data)
            {
                value = 1U;
            }
            write_data(value, offset, size);
        }
        else
        {
            write_data(data, offset, size);
        }
    }

    DataType data()
    {
        return m_data;
    }
private:

    uint32_t total_size_of_groups()
    {
        return bitter::total_size_of_groups_<Groups...>();
    }

    template<uint32_t Group>
    uint64_t group_size()
    {
        return group_size_<Group, Groups...>();
    }

    template<uint32_t Group, uint32_t NextGroup, uint32_t... InputGroups>
    uint64_t group_size_()
    {
        if (sizeof...(Groups) - Group == sizeof...(InputGroups) + 1)
        {
            return NextGroup;
        }
        else
        {
            return group_size_<Group, InputGroups...>();
        }
    }

    template<uint32_t Group>
    uint64_t group_size_()
    {
        return 0;
    }

    template<uint32_t Group>
    uint64_t group_offset()
    {
        return group_offset_<Group, Groups...>();
    }

    template <uint32_t Group, uint32_t NextGroup, uint32_t... InputGroups>
    uint64_t group_offset_()
    {
        if (sizeof...(Groups) - Group == sizeof...(InputGroups) + 1)
        {
            return 0;
        }
        else
        {
            return NextGroup + group_offset_<Group, InputGroups...>();
        }
    }

    template<uint32_t Group>
    uint64_t group_offset_()
    {
        return 0;
    }

    uint64_t create_mask(uint32_t size)
    {
        assert(size <= 64);
        return ~(0xFFFFFFFFFFFFFFFF >> (64 - size));
    }


    template<typename Type>
    void write_bit(Type value, uint32_t position)
    {
        assert(value == 0 || value == 1);
        Type mask = 0x001 << position;

        if(value == 0)
        {
            m_data &= ~mask;

        }
        else if(value == 1)
        {
            m_data |= mask;
        }
    }

    template<typename Type>
    void write_data(Type value_to_write, uint64_t offset, uint64_t size)
    {
        uint64_t checker_mask = create_mask(size);
        assert((checker_mask & value_to_write) == 0);

        auto current_offset = offset;

        for (uint64_t i = 0; i < size; ++i)
        {
            auto bit = (value_to_write >> i) & 0x1;
            write_bit(bit, current_offset);
            ++current_offset;
        }
    }

private:
    DataType m_data;
};
}
