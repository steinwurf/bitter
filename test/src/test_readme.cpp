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
    // Using an uint32_t data type divided into 4 bit fields each 8 bits in
    // size. The sum of the bit fields must match the number of bits in the data
    // type.
    auto writer = bitter::writer<uint32_t, 8, 8, 8, 8>();

    writer.field<0>(0xef); // Write bits 0-7
    writer.field<1>(0xbe); // Write bits 8-15
    writer.field<2>(0xad); // Write bits 16-23
    writer.field<3>(0xde); // Write bits 24-31

    assert(writer.data() == 0xdeadbeef);
}

TEST(test_readme, reading_a_bit_field)
{
    auto reader = bitter::reader<uint32_t, 8, 8, 8, 8>(0xdeadbeef);

    uint32_t value0 = reader.field<0>().read_as<uint8_t>();
    uint32_t value1 = reader.field<1>().read_as<uint8_t>();
    uint32_t value2 = reader.field<2>().read_as<uint8_t>();
    uint32_t value3 = reader.field<3>().read_as<uint8_t>();

    assert(value0 == 0xef); // Read bits 0-7
    assert(value1 == 0xbe); // Read bits 8-15
    assert(value2 == 0xad); // Read bits 16-23
    assert(value3 == 0xde); // Read bits 24-31
}
