// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file
#include <bitter/reader.hpp>

#include <cstdint>
#include <typeinfo>

#include <gtest/gtest.h>




TEST(test_bit_reader, read_bit)
{
    uint32_t input = 0x0FF0FF00U;
    auto reader = bitter::reader<uint32_t, 8, 8, 8, 8>(input);

    auto value = reader.get_field<0>().read_as<uint8_t>();
    EXPECT_EQ(0x00U, value);
    value = reader.get_field<1>().read_as<uint8_t>();
    EXPECT_EQ(0xFFU, value);
    value = reader.get_field<2>().read_as<uint8_t>();
    EXPECT_EQ(0xF0U, value);
    value = reader.get_field<3>().read_as<uint8_t>();
    EXPECT_EQ(0x0FU, value);
}

TEST(test_bit_reader, read_bit1)
{

    uint32_t input = 0x0FF0FF00U;
    auto reader = bitter::reader<uint32_t, 16, 16>(input);

    auto value = reader.get_field<0>().read_as<uint16_t>();
    EXPECT_EQ(0xFF00U, value);
    value = reader.get_field<1>().read_as<uint16_t>();
    EXPECT_EQ(0x0FF0U, value);
}

TEST(test_bit_reader, read_bit3)
{
    uint64_t input = 0xA50FF0A50FF0FF00U;
    auto reader = bitter::reader<uint64_t, 32, 32>(input);

    auto value = reader.get_field<0>().read_as<uint32_t>();
    EXPECT_EQ(0x0FF0FF00U, value);
    value = reader.get_field<1>().read_as<uint32_t>();
    EXPECT_EQ(0xA50FF0A5U, value);
}


TEST(test_bit_reader, read_bit4)
{

    uint64_t input = 0xA50FF0A50FF0FF00U;
    auto reader = bitter::reader<uint64_t, 64>(input);

    auto value = reader.get_field<0>().read_as<uint64_t>();
    EXPECT_EQ(0xA50FF0A50FF0FF00U, value);

}


TEST(test_bit_reader, read_bit5)
{
    uint8_t input = 0xF1;
    auto reader = bitter::reader<uint8_t, 1, 7>(input);

    auto value = reader.get_field<0>().read_as<bool>();
    EXPECT_TRUE(value);

    auto second_value = reader.get_field<1>().read_as<uint8_t>();
    EXPECT_EQ(120U, second_value);
}

TEST(test_bit_reader, read_bit6)
{
    uint8_t input = 0x81;
    auto reader = bitter::reader<uint8_t, 1, 7>(input);

    auto value = reader.get_field<0>().read_as<bool>();
    EXPECT_TRUE(value);

    auto second_value = reader.get_field<1>().read_as<uint8_t>();
    EXPECT_EQ(64U, second_value);
}

TEST(test_bit_reader, read_bit9)
{
    uint8_t input = 0xB5;
    auto reader = bitter::reader<uint8_t, 1, 1, 1, 1, 1, 1, 1, 1>(input);

    auto value = reader.get_field<0>().read_as<bool>();
    EXPECT_TRUE(value);

    value = reader.get_field<1>().read_as<bool>();
    EXPECT_FALSE(value);

    value = reader.get_field<2>().read_as<bool>();
    EXPECT_TRUE(value);

    value = reader.get_field<3>().read_as<bool>();
    EXPECT_FALSE(value);

    value = reader.get_field<4>().read_as<bool>();
    EXPECT_TRUE(value);

    value = reader.get_field<5>().read_as<bool>();
    EXPECT_TRUE(value);

    value = reader.get_field<6>().read_as<bool>();
    EXPECT_FALSE(value);

    value = reader.get_field<7>().read_as<bool>();
    EXPECT_TRUE(value);
}
