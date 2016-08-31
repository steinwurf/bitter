// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include <cstdint>
#include <vector>
#include <cassert>
#include <type_traits>

#include <iostream>

#include <endian/big_endian.hpp>
#include <endian/little_endian.hpp>

namespace bitter
{
template<class EndianType, uint32_t... Groups>
class bitfield_writer
{
public:
    bitfield_writer(std::vector<uint8_t> data):
    m_data(data)
    {
        m_number_of_groups = sizeof...(Groups);
    }

    template<typename Type, uint32_t Group>
    void write(Type value)
    {
        static_assert(std::is_same<Type, uint8_t>() ||
                      std::is_same<Type, uint16_t>() ||
                      std::is_same<Type, uint32_t>() ||
                      std::is_same<Type, uint64_t>(), "Invalid data type");

        assert(sizeof(Type) * 8 == group_size<Group>());

        auto offset = group_offset<Group>();
        auto size = group_size<Group>();

        auto checker_mask = create_mask(size);
        assert((checker_mask & value) == 0);

        std::vector<uint8_t> data_vector;
        data_vector.resize(sizeof(Type));

        EndianType::put(value, data_vector.data());
        writer_data(data_vector.data(), offset, size);
    }

    std::vector<uint8_t> data()
    {
        return m_data;
    }

private:
    template<uint32_t Group>
    uint32_t group_size()
    {
        return group_size<Group, Groups...>();
    }

    template<uint32_t Group, uint32_t NextGroup, uint32_t... InputGroups>
    uint32_t group_size_()
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
    uint32_t group_size_()
    {
        return 0;
    }

    template<uint32_t Group>
    uint32_t group_offset()
    {
        return group_offset_<Group, Groups...>();
    }

    template<uint32_t Group, uint32_t NextGroup, uint32_t... InputGroups>
    uint32_t group_offset_()
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
    uint32_t group_offset_()
    {
        return 0;
    }

    bool check_valid_group_size(uint32_t Group)
    {
        if (group_size<Group>() == 8 || group_size<Group>() == 16 ||
            group_size<Group>() == 32 || group_size<Group>() == 64)
        {
                return true;
        }
        else
        {
            return false;
        }
    }

    uint64_t create_mask(uint32_t size)
    {
        assert(size <= 64);
        return ~(0xFFFFFFFFFFFFFFFF >> (64 - size));
    }

    void write_bit(uint8_t value, uint8_t& dest, uint8_t position)
    {
        assert(value == 0 || value == 1);
        uint8_t mask = 0x001 << (7 - position);

        if(value == 0)
        {
            dest &= ~mask;
        }
        else if(value == 1)
        {
            dest |= mask;
        }
    }

    void write_data(uint8_t* data, uint32_t offset, uint32_t size)
    {
        uint32_t current_offset = offset;
        for (int i = size - 1; i >= 0; --i)
        {
            auto element_to_write = data[i];
            for (int j = 0; j < 8; ++i)
            {
                auto position = 7 - j;
                auto bit = (element_to_write >> position) & 0x1;

                auto byte_offset = current_offset / 8;
                auto bit_offset = current_offset % 8;
                auto& value = m_data[byte_offset];
                write_bit(bit, value, bit_offset);
                ++current_offset;
                if ((current_offset - offset) > size)
                {
                    return;
                }
            }
        }
    }


private:
    std::vector<uint8_t> m_data;
    uint64_t m_size;
    uint32_t m_number_of_groups;
};
}
