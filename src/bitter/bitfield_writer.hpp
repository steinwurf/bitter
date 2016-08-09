// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <cstdint>
#include <vector>
#include <cassert>
#include <iostream>

namespace bitter
{
template<int... Groups>
class bitfield_writer
{
public:
    bitfield_writer(std::vector<uint8_t> data, uint64_t bits):
    m_data(data),
    m_bits(bits)
    {

    }

    template<int Group, typename Type>
    void write(Type data)
    {
        auto offset = group_offset<Group>();
        auto size = group_size<Group>();
        if(std::is_same<Type, bool>::value)
        {
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
            write_data<Type>(data, offset, size);
        }

    }

    std::vector<uint8_t> data()
    {
        return m_data;
    }

private:

    template<int Group>
    uint64_t group_size()
    {
        return group_size_<Group, Groups...>();
    }

    template<int Group, int NextGroup, int... InputGroups>
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

    template<int Group>
    uint64_t group_size_()
    {
        return 0;
    }

    template<int Group>
    uint64_t group_offset()
    {
        return group_offset_<Group, Groups...>();
    }

    template <int Group, int NextGroup, int... InputGroups>
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

    template<int Group>
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

private:
    std::vector<uint8_t> m_data;
    uint64_t m_bits;
};
}
