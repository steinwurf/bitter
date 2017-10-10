// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <bitter/lsb0_writer.hpp>
#include <bitter/lsb0_reader.hpp>
#include <bitter/msb0_writer.hpp>
#include <bitter/msb0_reader.hpp>

#include <gtest/gtest.h>

#include <cassert>

// @todo enable
//
TEST(test_readme, writing_a_lsb0_bit_field)
{
    // Using an uint32_t data type divided into 4 bit fields each 8 bits in
    // size. The sum of the bit fields must match the number of bits in the data
    // type.
    auto writer = bitter::lsb0_writer<uint32_t, 8, 8, 8, 8>();

    writer.field<0>(0x12); // Write bits 0-7
    writer.field<1>(0x34); // Write bits 8-15
    writer.field<2>(0x56); // Write bits 16-23
    writer.field<3>(0x78); // Write bits 24-31

    assert(writer.data() == 0x78563412);
}

TEST(test_readme, writing_a_msb0_bit_field)
{
    // Using an uint32_t data type divided into 4 bit fields each 8 bits in
    // size. The sum of the bit fields must match the number of bits in the data
    // type.
    auto writer = bitter::msb0_writer<uint32_t, 8, 8, 8, 8>();

    writer.field<0>(0x12); // Write bits 24-31
    writer.field<1>(0x34); // Write bits 16-23
    writer.field<2>(0x56); // Write bits 8-15
    writer.field<3>(0x78); // Write bits 0-7

    assert(writer.data() == 0x12345678);
}

TEST(test_readme, reading_a_lsb0_bit_field)
{
    auto reader = bitter::lsb0_reader<uint32_t, 8, 8, 8, 8>(0x12345678);

    uint8_t value0 = reader.field<0>().read_as<uint8_t>(); // Read bits 0-7
    uint8_t value1 = reader.field<1>().read_as<uint8_t>(); // Read bits 8-15
    uint8_t value2 = reader.field<2>().read_as<uint8_t>(); // Read bits 16-23
    uint8_t value3 = reader.field<3>().read_as<uint8_t>(); // Read bits 24-31

    assert(value0 == 0x78);
    assert(value1 == 0x56);
    assert(value2 == 0x34);
    assert(value3 == 0x12);
}

TEST(test_readme, reading_a_msb0_bit_field)
{
    auto reader = bitter::msb0_reader<uint32_t, 8, 8, 8, 8>(0x12345678);

    uint8_t value0 = reader.field<0>().read_as<uint8_t>(); // Read bits 0-7
    uint8_t value1 = reader.field<1>().read_as<uint8_t>(); // Read bits 8-15
    uint8_t value2 = reader.field<2>().read_as<uint8_t>(); // Read bits 16-23
    uint8_t value3 = reader.field<3>().read_as<uint8_t>(); // Read bits 24-31

    assert(value0 == 0x12);
    assert(value1 == 0x34);
    assert(value2 == 0x56);
    assert(value3 == 0x78);
}
