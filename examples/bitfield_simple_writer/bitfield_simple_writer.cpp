// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#include <bitter/bitfield_writer.hpp>

#include <endian/little_endian.hpp>

#include <cstdint>
#include <vector>
#include <iostream>
#include <cstdint>

void print_byte(uint8_t byte)
{
    for(int i = 0; i  < 8; ++i)
    {
        auto position = 7 - i;
        auto bit = (byte >> position) & 0x1;
        std::cout << static_cast<uint32_t>(bit);
    }
    std::cout << " ";
}

int main()
{
    auto writer = bitter::bitfield_writer<uint32_t, 1, 7, 8, 16>();

    bool first = true;
    writer.write<0>(first);
    uint8_t value = 32U;
    writer.write<1>(value);
    value = 128U;
    writer.write<2>(value);
    uint32_t larger_value = 2050;
    writer.write<3>(larger_value);


    std::cout << "Data as number: " << writer.data() << std::endl;
    auto data_pointer = writer.data_as_pointer();

    for (uint32_t i = 0; i < sizeof(uint32_t); ++i)
    {
        print_byte(data_pointer[i]);
    }
    return 0;
}
