// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <bitter/detail/field_get.hpp>

#include <bitter/lsb0.hpp>
#include <bitter/msb0.hpp>
#include <bitter/types.hpp>

#include <cstdint>

#include <gtest/gtest.h>

TEST(test_field_get, field_u8)
{
    uint8_t value = 0b10000000;

    {
        auto f0 = bitter::field_get<bitter::u8, bitter::msb0, 0, 1, 7>(value);

        auto f1 = bitter::field_get<bitter::u8, bitter::msb0, 1, 1, 7>(value);

        EXPECT_EQ(f0, 0b1);
        EXPECT_EQ(f1, 0b0000000);
    }
    {
        auto f0 = bitter::field_get<bitter::u8, bitter::lsb0, 0, 1, 7>(value);
        auto f1 = bitter::field_get<bitter::u8, bitter::lsb0, 1, 1, 7>(value);

        EXPECT_EQ(f0, 0b0);
        EXPECT_EQ(f1, 0b1000000);
    }
}

TEST(test_field_get, field_u24)
{
    uint32_t value = 0xF0000F;

    {
        auto f0 = bitter::field_get<bitter::u24, bitter::msb0, 0, 4, 20>(value);
        auto f1 = bitter::field_get<bitter::u24, bitter::msb0, 1, 4, 20>(value);

        EXPECT_EQ(f0, 0xFU);
        EXPECT_EQ(f1, 0x0000FU);
    }
    {
        auto f0 = bitter::field_get<bitter::u24, bitter::lsb0, 0, 4, 20>(value);
        auto f1 = bitter::field_get<bitter::u24, bitter::lsb0, 1, 4, 20>(value);

        EXPECT_EQ(f0, 0xFU);
        EXPECT_EQ(f1, 0xF0000U);
    }
}
