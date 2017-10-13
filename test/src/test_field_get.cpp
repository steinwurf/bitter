// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <bitter/field_get.hpp>

#include <bitter/msb0.hpp>
#include <bitter/lsb0.hpp>

#include <cstdint>

#include <gtest/gtest.h>

TEST(test_field_get, field)
{
    uint8_t value = 0b10000000;

    {
        auto f0 = bitter::field_get<uint8_t, bitter::msb0, 0, 1, 7>(value);
        auto f1 = bitter::field_get<uint8_t, bitter::msb0, 1, 1, 7>(value);

        EXPECT_EQ(f0, 0b1);
        EXPECT_EQ(f1, 0b0000000);
    }
    {
        auto f0 = bitter::field_get<uint8_t, bitter::lsb0, 0, 1, 7>(value);
        auto f1 = bitter::field_get<uint8_t, bitter::lsb0, 1, 1, 7>(value);

        EXPECT_EQ(f0, 0b0);
        EXPECT_EQ(f1, 0b1000000);
    }
}
