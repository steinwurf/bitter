// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <bitter/field_get.hpp>

#include <bitter/types.hpp>

#include <cstdint>

#include <gtest/gtest.h>

TEST(test_field_get, field)
{
    uint8_t value = 0b11111111;

    EXPECT_EQ(0b1, (bitter::field_get<bitter::u8, 0, 1, 7>(value)));
    EXPECT_EQ(0b1111111, (bitter::field_get<bitter::u8, 1, 1, 7>(value)));
}

TEST(test_field_get, field2)
{
    uint16_t value = 1024U;
    EXPECT_EQ(0U, (bitter::field_get<bitter::u16, 0, 8, 8>(value)));
    EXPECT_EQ(4U, (bitter::field_get<bitter::u16, 1, 8, 8>(value)));
}

TEST(test_field_get, field3)
{
    uint32_t value = 0xF0000FU;
    EXPECT_EQ(0xFU, (bitter::field_get<bitter::u24, 0, 4, 20>(value)));
    EXPECT_EQ(0xFU, (bitter::field_get<bitter::u24, 1, 4, 20>(value)));
}
