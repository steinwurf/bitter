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
    bitfield_writer(uint8_t* data, uint64_t bits):
    m_data(data),
    m_bits(bits)
    {

    }

    template<int Group, typename Type>
    void write(Type data)
    {

        auto size = group_size<Group>();
        // assert(sizeof(data) <= );
        auto offset = group_offset<Group>();

        if((offset + size) / 8 <= 1 && !std::is_same<Type, bool>::value)
        {
            // Is data just larger than a single byte
            if(size % 8 != 0)
            {
                if(size / 8 == 1)
                {
                    std::cout << "deo" << std::endl;
                    auto prior_bits = overflowing_bits(offset, size);
                    uint8_t prior_data = data >> (size - prior_bits);
                    uint8_t following_data = data << prior_bits;
                    write_<Type>(prior_data, offset);
                    write_<Type>(following_data, offset + prior_bits);
                }
                else
                {
                    auto splitted_data = data_split_to_byte<Type>(data, size);
                    write_vector(splitted_data, offset);
                }
            }
            else
            {
                auto prior_bits = overflowing_bits(offset, size);
                uint8_t prior_data = data >> (size - prior_bits);
                write_<uint8_t>(prior_data, offset);
                data = (data << prior_bits) >> prior_bits;
                auto splitted_data =
                     data_split_to_byte<Type>(data, offset + prior_bits);
                write_vector(splitted_data, offset + prior_bits);

            }

        }
        else
        {
            if(std::is_same<Type, bool>::value)
            {
                if(data)
                {

                    write_<uint8_t>(1U, offset);
                }
                else
                {
                    write_<uint8_t>(0U, offset);
                }
            }
            else
            {
                write_<Type>(data, offset);
            }
        }

    }

    uint8_t* data()
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

    template<typename Type>
    void write_(Type data, uint64_t offset)
    {
        std::cout << "Offset: " << offset << std::endl;
        auto index = offset / 8;
        std::cout << "index: " << static_cast<int>(index) << std::endl;
        auto shift = 7 - (offset - (index * 8));
        uint8_t x = m_data[index] = (data);
        m_data[index] = m_data[index] | data;
    }

    void write_vector(std::vector<uint8_t> data, uint64_t offset)
    {
        for(uint8_t entry : data)
        {
            write_<uint8_t>(entry, offset);
            offset += 8;
        }
    }

    template<typename Type>
    std::vector<uint8_t> data_split_to_byte(Type data, uint64_t size)
    {
        assert(size <= 64);
        std::vector<uint8_t> splitted_data(size / 8);
        if(size == 16)
        {
            splitted_data.push_back((data >> 8) & 0x00FF);
            splitted_data.push_back(data & 0x00FF);
        }
        else if(size == 32)
        {
            splitted_data.push_back((data >> 24) & 0x00FF);
            splitted_data.push_back((data >> 16) & 0x00FF);
            splitted_data.push_back((data >> 8) & 0x00FF);
            splitted_data.push_back(data & 0x00FF);
        }
        else
        {
            splitted_data.push_back((data >> 56) & 0x00FF);
            splitted_data.push_back((data >> 48) & 0x00FF);
            splitted_data.push_back((data >> 40) & 0x00FF);
            splitted_data.push_back((data >> 32) & 0x00FF);
            splitted_data.push_back((data >> 24) & 0x00FF);
            splitted_data.push_back((data >> 16) & 0x00FF);
            splitted_data.push_back((data >> 8) & 0x00FF);
            splitted_data.push_back(data & 0x00FF);
        }
        return splitted_data;
    }

    uint64_t overflowing_bits(uint64_t offset, uint64_t size)
    {
        uint64_t bits = 0;
        while(((offset + size) - bits) % 8 != 0)
        {
            bits++;
        }
        return bits;
    }


private:
    uint8_t* m_data;
    uint64_t m_bits;
};
}
