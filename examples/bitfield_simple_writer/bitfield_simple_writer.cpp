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
    // Set up stream for print and used for reset
    std::ios state(NULL);
    state.copyfmt(std::cout);

    std::vector<uint8_t> dummy;
    dummy.resize(5);
    auto writer = bitter::bitfield_writer<endian::little_endian,
                                          16, 8, 1>(dummy);
    //writer.write<1, bool>(true);
    //writer.write<2, uint8_t>(254);

    writer.write<0, uint16_t>(34U);
    writer.write<1, uint8_t>(12U);
    writer.write<2, bool>(true);
    //writer.write<0, bool>(true);

    auto z = writer.data();

    for(auto x : z)
    {
        print_byte(x);
    }
    std::cout << "" << std::endl;

    return 0;
}
