// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <bitter/writer.hpp>
#include <bitter/reader.hpp>

#include <gtest/gtest.h>

#include <cassert>

TEST(test_readme, writing_a_bit_field)
{
    // Write into a 16 bit data type divided into 3 bit fields of size 1, 2, and
    // 13 bits respectively. The sum of sizes of the bit fields must match the
    // number of bits in the choosen data type.
    auto writer = bitter::writer<uint16_t, 1, 2, 13>();

    writer.field<0>(1); // Write bit 0
    writer.field<1>(1); // Write bits 1-2
    writer.field<2>(1); // Write bits 3-15
    assert(writer.data() == 0b0000000000001011);
}

TEST(test_readme, reading_a_bit_field)
{
    // Read from a 16 bit data type divided into 3 bit fields of size 1, 2, and
    // 13 bits respectively.
    auto reader = bitter::reader<uint16_t, 1, 2, 13>(0b0000000000001011);

    bool value0 = reader.field<0>().read_as<bool>(); // Read bit 0
    uint8_t value1 = reader.field<1>().read_as<uint8_t>(); // Read bits 1-2
    uint16_t value2 = reader.field<2>().read_as<uint16_t>(); // Read bits 3-15

    assert(value0 == 1);
    assert(value1 == 1);
    assert(value2 == 1);
}
