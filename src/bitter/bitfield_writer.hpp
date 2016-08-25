// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include <cstdint>
#include <vector>
#include <cassert>
#include <type_traits>

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

    template<uint32_t Group, typename Type>
    void write(Type data)
    {
        // Check if Group actually exists
        //std::cout << "number of groups" << m_number_of_groups << std::endl;
        assert(Group < m_number_of_groups);

        // Determine offset for group and size for the group
        auto offset = group_offset<Group>();
        auto size = group_size<Group>();

        if(is_endian_shift_needed<Type>(size))
        {
            data = data << (sizeof(Type) - size);
        }



        if(std::is_same<Type, bool>::value)
        {
            // If the bool value is true, write 0000 0001
            // If the bool value is false, write 0000 0000
            if(data)
            {
                write_data<uint8_t>(1U, offset, size);
            }
            else
            {
                write_data<uint8_t>(0U, offset, size);
            }
        }
        else
        {
            // Based
            if(size <= 8)
            {
                write_data<uint8_t>(data, offset, size);
            }
            else if(size <= 16)
            {
                write_data<uint16_t>(data, offset, size);
            }
            else if(size <= 32)
            {
                write_data<uint32_t>(data, offset, size);
            }
            else if(size <= 64)
            {
                write_data<uint64_t>(data, offset, size);
            }
        }

    }

    std::vector<uint8_t> data()
    {
        return m_data;
    }

private:
    template<uint32_t Group>
    uint64_t group_size()
    {
        return group_size_<Group, Groups...>();
    }

    template<uint32_t Group, uint32_t NextGroup, uint32_t... InputGroups>
    uint64_t group_size_()
    {
        if(sizeof...(Groups) - Group == sizeof...(InputGroups) + 1)
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
        if(sizeof...(Groups) - Group == sizeof...(InputGroups) + 1)
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

    template<typename Type>
    void write_data(Type value_to_write, uint64_t offset, uint64_t size)
    {

        uint64_t checker_mask = create_mask(size);
        assert((checker_mask & value_to_write) == 0);

        value_to_write = value_to_write << ((sizeof(value_to_write) * 8) - size);

        uint8_t* data_to_write = (uint8_t*) &value_to_write;
        uint32_t data_to_write_size = sizeof(value_to_write);

        // If we want little endian, this will convert data to little endian
        if(is_little_endian())
        {
            auto offset_value = (((sizeof(value_to_write) * 8) - size) / 8);
            EndianType::template put<Type>(value_to_write, data_to_write);
            // Do so the pointer only takes needed data
            // This is for removing unwanted zeros in pointer
            data_to_write = data_to_write + offset_value;
            data_to_write_size -= offset_value;
        }


        uint64_t current_offset = offset;
        for(int i = data_to_write_size - 1; i >= 0; --i)
        {
            auto data_to_write_element = data_to_write[i];

            for(int j = 0; j < 8; j++)
            {
                auto position = 7 - j;
                auto bit = (data_to_write_element >> position) & 0x1;

                uint64_t byte_offset = current_offset / 8;
                uint64_t bit_offset = current_offset % 8;
                auto& value = m_data[byte_offset];

                write_bit(bit, value, bit_offset);
                ++current_offset;
                if((current_offset - offset) > size)
                {
                    return;
                }
            }
        }
    }

    template<typename Type>
    bool is_endian_shift_needed(uint64_t size)
    {
        if(is_little_endian())
        {
            if(size < (sizeof(Type) * 8))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        return false;
    }

    bool is_little_endian()
    {
        return std::is_same<EndianType, endian::little_endian()>();
    }

private:
    std::vector<uint8_t> m_data;
    uint64_t m_size;
    uint32_t m_number_of_groups;
};
}
