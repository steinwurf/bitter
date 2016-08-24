// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#include <bitter/bitfield_reader.hpp>

#include <endian/little_endian.hpp>

#include <vector>
#include <cstdint>
#include <iostream>

int main()
{

    std::vector<uint8_t> data;
    data.push_back(129U);
    data.push_back(255U);

    auto reader = bitter::bitfield_reader<endian::little_endian,
                                          1,1,1,1,
                                          1,1,1,1,
                                          8>(data);

    auto b1 = reader.read<bool, 0>();
    std::cout << "Boolean 1: " << b1 << std::endl;
    auto b2 = reader.read<bool, 1>();
    std::cout << "Boolean 2: " << b2 << std::endl;
    auto b3 = reader.read<bool, 2>();
    std::cout << "Boolean 3: " << b3 << std::endl;
    auto b4 = reader.read<bool, 3>();
    std::cout << "Boolean 4: " << b4 << std::endl;
    auto b5 = reader.read<bool, 4>();
    std::cout << "Boolean 5: " << b5 << std::endl;
    auto b6 = reader.read<bool, 5>();
    std::cout << "Boolean 6: " << b6 << std::endl;
    auto b7 = reader.read<bool, 6>();
    std::cout << "Boolean 7: " << b7 << std::endl;
    auto b8 = reader.read<bool, 7>();
    std::cout << "Boolean 8: " << b8 << std::endl;

    auto number = reader.read<uint8_t, 8>();

    std::cout << "Number: " << static_cast<int>(number) << std::endl;

    return 0;
}
