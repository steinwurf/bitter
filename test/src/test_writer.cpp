// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <bitter/lsb0_writer.hpp>
#include <bitter/msb0_writer.hpp>

#include <cstdint>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

TEST(test_bit_writer, write_integer)
{
    {
        auto writer = bitter::lsb0_writer<uint8_t, 4, 4>();
        writer.field<0>(0x0U);
        writer.field<1>(0xFU);
        auto value = writer.data();
        EXPECT_EQ(value, 0xF0U);
    }
    {
        auto writer = bitter::lsb0_writer<uint16_t, 8, 8>();
        writer.field<0>(0xF0U);
        writer.field<1>(0x0FU);
        auto value = writer.data();
        EXPECT_EQ(value, 0x0FF0U);
    }
    {
        auto writer = bitter::lsb0_writer<uint32_t, 16, 16>();
        writer.field<0>(0xF0F0U);
        writer.field<1>(0x0F0FU);
        auto value = writer.data();
        EXPECT_EQ(value, 0x0F0FF0F0U);
    }
    {
        auto writer = bitter::lsb0_writer<uint64_t, 32, 32>();
        writer.field<0>(0xF0F0F0F0U);
        writer.field<1>(0x0F0F0F0FU);
        auto value = writer.data();
        EXPECT_EQ(value, 0x0F0F0F0FF0F0F0F0U);
    }
}

TEST(test_bit_writer, write_bit)
{
    {
        auto writer = bitter::lsb0_writer<bitter::u8, 1, 7>();
        writer.field<0>(true);
        uint8_t input = 0b1000000;
        writer.field<1>(input);
        auto value = writer.data();
        EXPECT_EQ(value, 0b10000001U);
    }
    {
        auto writer = bitter::msb0_writer<bitter::u8, 1, 7>();
        writer.field<0>(true);
        uint8_t input = 0b1000000;
        writer.field<1>(input);
        auto value = writer.data();
        EXPECT_EQ(value, 0b11000000U);
    }
}

TEST(test_bit_writer, write_bit_1)
{
    {
        auto writer = bitter::lsb0_writer<bitter::u16, 16>();
        uint16_t input = 2050U;
        writer.field<0>(input);

        auto value = writer.data();
        EXPECT_EQ(value, 2050U);
    }
    {
        auto writer = bitter::msb0_writer<bitter::u16, 16>();
        uint16_t input = 2050U;
        writer.field<0>(input);

        auto value = writer.data();
        EXPECT_EQ(value, 2050U);
    }
}

TEST(test_bit_writer, write_bit_u24)
{
    {
        auto writer = bitter::lsb0_writer<bitter::u24, 16, 8>();
        writer.field<0>(0xFF00);

        auto value = writer.data();
        EXPECT_EQ(value, 0xFF00U);

        writer.field<1>(0xFF);

        value = writer.data();
        EXPECT_EQ(value, 0xFFFF00U);
    }
    {
        auto writer = bitter::msb0_writer<bitter::u24, 16, 8>();
        writer.field<0>(0xFF00);

        auto value = writer.data();
        EXPECT_EQ(value, 0xFF0000U);

        writer.field<1>(0xFF);

        value = writer.data();
        EXPECT_EQ(value, 0xFF00FFU);
    }
}

TEST(test_bit_writer, write_bit_2)
{
    {
        auto writer = bitter::lsb0_writer<bitter::u32, 32>();

        uint32_t input = 323794U;
        writer.field<0>(input);

        auto value = writer.data();
        EXPECT_EQ(value, 323794U);
    }
    {
        auto writer = bitter::msb0_writer<bitter::u32, 32>();

        uint32_t input = 323794U;
        writer.field<0>(input);

        auto value = writer.data();
        EXPECT_EQ(value, 323794U);
    }
}

TEST(test_bit_writer, write_bit_3)
{
    {
        auto writer = bitter::lsb0_writer<bitter::u64, 32, 32>();

        uint32_t input = 0x22222222;
        writer.field<0>(input);
        input = 0x44444444;
        writer.field<1>(input);
        auto value = writer.data();
        EXPECT_EQ(value, 0x4444444422222222U);
    }
    {
        auto writer = bitter::msb0_writer<bitter::u64, 32, 32>();

        uint32_t input = 0x22222222;
        writer.field<0>(input);
        input = 0x44444444;
        writer.field<1>(input);
        auto value = writer.data();
        EXPECT_EQ(value, 0x2222222244444444U);
    }
}

TEST(test_bit_writer, write_bit_4)
{
    {
        auto writer = bitter::lsb0_writer<bitter::u32, 16, 16>();
        uint16_t input = 0x1234;
        writer.field<0>(input);

        input = 0x4321;
        writer.field<1>(input);

        auto value = writer.data();
        EXPECT_EQ(value, 0x43211234U);
    }
    {
        auto writer = bitter::msb0_writer<bitter::u32, 16, 16>();
        uint16_t input = 0x1234;
        writer.field<0>(input);

        input = 0x4321;
        writer.field<1>(input);

        auto value = writer.data();
        EXPECT_EQ(value, 0x12344321U);
    }
}

TEST(test_bit_writer, write_bit_5)
{
    {
        auto writer = bitter::lsb0_writer<bitter::u32, 8, 8, 8, 8>();
        uint8_t input = 0x11;
        writer.field<0>(input);

        input = 0x22;
        writer.field<1>(input);

        input = 0x33;
        writer.field<2>(input);

        input = 0x44;
        writer.field<3>(input);

        auto value = writer.data();
        EXPECT_EQ(value, 0x44332211U);
    }
    {
        auto writer = bitter::msb0_writer<bitter::u32, 8, 8, 8, 8>();
        uint8_t input = 0x11;
        writer.field<0>(input);

        input = 0x22;
        writer.field<1>(input);

        input = 0x33;
        writer.field<2>(input);

        input = 0x44;
        writer.field<3>(input);

        auto value = writer.data();
        EXPECT_EQ(value, 0x11223344U);
    }
}
