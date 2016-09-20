// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#include <bitter/reader.hpp>

#include <cstdint>
#include <cassert>
#include <iostream>

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

    uint32_t value = 0x20880A0U; //0000001000001000 10000000 1010000 0
    auto reader = bitter::reader<uint32_t, 1, 7, 8, 16>(value);

    auto first_field = reader.get_field<0>().read_as<bool>();
    assert(first_field == false);

    auto second_field = reader.get_field<1>().read_as<uint8_t>();
    assert(second_field == 80U);

    auto third_field = reader.get_field<2>().read_as<uint8_t>();
    assert(third_field == 128U);

    auto fourth_field = reader.get_field<3>().read_as<uint16_t>();;
    assert(fourth_field == 520U);

    return 0;
}
