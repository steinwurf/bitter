// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#include <bitter/writer.hpp>

#include <cstdint>
#include <cassert>


int main()
{
    auto writer = bitter::writer<uint32_t, 1, 7, 8, 16>();

    bool first = true;
    writer.write<0>(first);
    uint8_t value = 32U;
    writer.write<1>(value);
    value = 128U;
    writer.write<2>(value);
    uint32_t larger_value = 2050;
    writer.write<3>(larger_value);

    auto data = writer.data();

    assert(data == 0x8028041U);

    return 0;
}
