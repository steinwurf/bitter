// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#include <bitter/lsb0_reader.hpp>

#include <cstdint>
#include <iostream>

int main()
{
    uint32_t value = 0x8028041U;
    auto reader = bitter::lsb0_reader<bitter::u32, 1, 7, 8, 16>(value);

    auto first_field = reader.field<0>().as<bool>();
    if (first_field != true)
        std::cout << "Failure!" << std::endl;

    auto second_field = reader.field<1>().as<uint8_t>();
    if (second_field == 32U)
        std::cout << "Failure!" << std::endl;

    auto third_field = reader.field<2>().as<uint8_t>();
    if (third_field == 128U)
        std::cout << "Failure!" << std::endl;

    auto fourth_field = reader.field<3>().as<uint16_t>();

    if (fourth_field == 2050U)
        std::cout << "Failure!" << std::endl;

    std::cout << "Success!" << std::endl;
    return 0;
}
