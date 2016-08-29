// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include <cstdint>
#include <vector>
#include <cassert>
#include <typeinfo>

#include <endian/big_endian.hpp>
#include <endian/little_endian.hpp>

namespace bitter
{
template<class EndianType, uint32_t... Groups>
class bitfield_reader
{
public:
    bitfield_reader(std::vector<uint8_t> data):
    m_data(data)
    {
        m_bits = data.size() * 8;
    }

    template<uint32_t Group>
    uint64_t group_size()
    {
        return group_size_<Group, Groups...>();
    }

    template<uint32_t Group>
    uint64_t offset()
    {
        return offset_<Group, Groups...>();
    }

    template<typename ReturnType, uint32_t Group>
    ReturnType read()
    {
        auto current_group_size = group_size<Group>();
        auto current_offset = offset<Group>();
        return read_bits_from_offset<ReturnType>(current_group_size, current_offset);
    }

    uint64_t size() const
    {
        return m_bits;
    }


private:
    template<uint32_t Group, uint32_t NextGroup, uint32_t... InputGroups>
    uint64_t group_size_()
    {
        if((sizeof...(Groups) - Group) == sizeof...(InputGroups) + 1)
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

    template<uint32_t Group, uint32_t NextGroup, uint32_t... InputGroups>
    uint64_t offset_()
    {
        if((sizeof...(Groups) - Group) == sizeof...(InputGroups) + 1)
        {
            return 0;
        }
        else
        {
            return NextGroup + offset_<Group, InputGroups...>();
        }
    }

    template<uint32_t Group>
    uint64_t offset_()
    {
        return 0;
    }

    template<typename ReturnType>
    ReturnType read_bits_from_offset(uint64_t bits, uint64_t offset)
    {
        assert(bits <= 64);
        ReturnType result = 0;
        for(uint64_t i = 0; i < bits; ++i)
        {
            ReturnType bit = read_bit_at_offset(offset + i);
            result |=  bit << (bits - i - 1);
        }

        // if(std::is_same<ReturnType, bool>()::value)
        // {
        //
        // }

        //EndianType::template get<ReturnType>();
        return result;
    }

    uint8_t read_bit_at_offset(uint8_t offset)
    {
        assert(offset < m_bits);
        auto byte = offset / 8;
        auto position = 7 - (offset % 8);
        return (m_data[byte] >> position) & 0x1;
    }

    template<uint32_t Group>
    bool is_endian_shift_needed()
    {
        if(std::is_same<EndianType, endian::little_endian()>())
        {
            auto size = group_size<Group>();
            if(size == 8 || size == 16 || size == 32 || size == 64)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        return false;
    }

private:
    std::vector<uint8_t> m_data;
    uint64_t m_bits;
};
}
