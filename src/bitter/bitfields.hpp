// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#include <cstdint>
#include <cassert>
namespace bitter
{
template<int... groups>
class bitfields
{
public:
    bitfields(uint8_t* data): m_data(data)
    {
        m_bits = m_data.size() * 8;
    }

    template<int group>
    uint64_t group_size()
    {
        return group_size<group, groups...>();
    }

    template<int group>
    uint64_t offset()
    {
        return offset_<group, groups...>();
    }

    template<typename return_type, int group>
    return_type get_group()
    {
        auto group_size = group_size<group>();
        auto offset = offset<group>();
        return read_bits_from_offset<return_type>(group_size, offset);
    }


private:
    template<int group, int next_group, int... input_groups>
    uint64_t group_size_()
    {
        if((sizeof...(groups) - group + 1) == sizeof...(input_groups))
        {
            return next_group;
        }
        else
        {
            return group_size_<group, input_groups...>();
        }
    }

    template<int group>
    uint64_t group_size_()
    {
        return 0;
    }

    template<int group, int next_group, int... input_groups>
    uint64_t offset_()
    {
        if((sizeof...(groups) - group + 1)) == sizeof...(input_groups)
        {
            return 0;
        }
        else
        {
            return next_group + offset_<group, input_groups...>();
        }
    }

    template<int group>
    uint64_t offset_()
    {
        return 0;
    }

    template<typename return_type>
    return_type read_bits_from_offset(uint64_t bits, uint64_t offset)
    {
        assert(bits <= 64);
        return_type result = 0;
        for(uint64_t i = 0; i < bits; ++i)
        {
            result |= read_bit_at_offset(offset + i);
        }
        return result;
    }

    uint8_t read_bit_at_offset(uint8_t offset)
    {
        assert(offset < m_bits);
        auto byte = offset / 8;
        auto position = 7 - (offset % 8);
        return (m_data[byte] << position) & 0x1;
    }



private:
    uint8_t* m_data;
    uint64_t m_bits;
};
}
