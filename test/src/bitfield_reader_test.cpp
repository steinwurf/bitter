// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file
#include <bitter/bitfield_reader.hpp>

#include <cstdint>

#include <gtest/gtest.h>

#include <typeinfo>

#include <iostream>

TEST(test_bit_reader, read_bit)
{
    uint32_t input = 0x0FF0FF00U;
    auto reader = bitter::bitfield_reader<uint32_t, 8, 8, 8, 8>(input);

    auto value = reader.read<uint8_t, 0>();
    EXPECT_EQ(0x00U, value);
    value = reader.read<uint8_t, 1>();
    EXPECT_EQ(0xFFU, value);
    value = reader.read<uint8_t, 2>();
    EXPECT_EQ(0xF0U, value);
    value = reader.read<uint8_t, 3>();
    EXPECT_EQ(0x0FU, value);
}

TEST(test_bit_reader, read_bit2)
{

    uint32_t input = 0x0FF0FF00U;
    auto reader = bitter::bitfield_reader<uint32_t, 16, 16>(input);

    auto value = reader.read<uint16_t, 0>();
    EXPECT_EQ(0xFF00U, value);
    value = reader.read<uint16_t, 1>();
    EXPECT_EQ(0x0FF0U, value);
}

TEST(test_bit_reader, read_bit3)
{
    uint64_t input = 0xA50FF0A50FF0FF00U;
    auto reader = bitter::bitfield_reader<uint64_t, 32, 32>(input);

    auto value = reader.read<uint32_t, 0>();
    EXPECT_EQ(0x0FF0FF00U, value);
    value = reader.read<uint32_t, 1>();
    EXPECT_EQ(0xA50FF0A5U, value);
}


TEST(test_bit_reader, read_bit4)
{

    uint64_t input = 0xA50FF0A50FF0FF00U;
    auto reader = bitter::bitfield_reader<uint64_t, 64>(input);

    auto value = reader.read<uint64_t, 0>();
    EXPECT_EQ(0xA50FF0A50FF0FF00U, value);

}

TEST(test_bit_reader, read_bit5)
{
    uint8_t input = 0x01;
    auto reader = bitter::bitfield_reader<uint8_t, 1>(input);

    auto value = reader.read<bool, 0>();
    EXPECT_TRUE(value);

}

TEST(test_bit_reader, read_bit6)
{
    uint8_t input = 0x00;
    auto reader = bitter::bitfield_reader<uint8_t, 1>(input);

    auto value = reader.read<bool, 0>();
    EXPECT_FALSE(value);

}
