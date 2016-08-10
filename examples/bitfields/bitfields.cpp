// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#include <vector>
#include <iostream>
#include <cstdint>
#include <bitset>

#include <bitter/bitfield_reader.hpp>

int main()
{
    std::vector<uint8_t> data
    {
        0x00, //0000 0000
        0xFF, //1111 1111
        0xF0, //1111 0000
        0x0F, //0000 1111
        0xA5, //1010 0101
        0x00, //0000 0000
        0xFF, //1111 1111
        0xF0, //1111 0000
        0x0F, //0000 1111
        0xA5, //1010 0101
        0x00, //0000 0000
        0xFF, //1111 1111
        0xF0, //1111 0000
        0x0F, //0000 1111
        0xA5, //1010 0101
        0x00, //0000 0000
        0xFF, //1111 1111
        0xF0, //1111 0000
        0x0F, //0000 1111
        0xA5, //1010 0101
    };

    // Set up stream for print
    std::ios state(NULL);
    state.copyfmt(std::cout);

    auto bf = bitter::bitfield_reader<8,16,32,64>(data.data(), data.size() * 8);
    auto group_zero = bf.get<uint8_t, 0>();
    auto group_one = bf.get<uint16_t, 1>();
    auto group_two = bf.get<uint32_t, 2>();
    auto group_three = bf.get<uint64_t, 3>();
    std::cout << "Group 0 size: " << bf.group_size<0>() << " offset: " << bf.offset<0>() << std::endl;
    std::cout << "Group " << 0 << ": " << std::hex << static_cast<int>(group_zero) << std::endl;
    std::cout.copyfmt(state);
    std::cout << "Group 1 size: " << bf.group_size<1>() << " offset: " << bf.offset<1>() << std::endl;
    std::cout << "Group " << 1 << ": " << std::hex << static_cast<int>(group_one) << std::endl;
    std::cout.copyfmt(state);
    std::cout << "Group 2 size: " << bf.group_size<2>() << " offset: " << bf.offset<2>() << std::endl;
    std::cout << "Group " << 2 << ": " << std::hex << static_cast<int>(group_two) << std::endl;
    std::cout.copyfmt(state);
    std::cout << "Group 3 size: " << bf.group_size<3>() << " offset: " << bf.offset<3>() << std::endl;
    std::cout << "Group " << 3 << ": " << std::hex << group_three << std::endl;
    std::cout.copyfmt(state);
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;
}
