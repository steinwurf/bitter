// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <bitter/field_set.hpp>

#include <bitter/lsb0.hpp>
#include <bitter/msb0.hpp>

#include <cstdint>

#include <gtest/gtest.h>

TEST(test_field_set, field_set)
{
    {
        uint16_t temp = 0U;
        temp = bitter::field_set<
               uint16_t, bitter::lsb0, 0, 8, 8>(temp, 65U);
        EXPECT_EQ(65U, temp);
        temp = bitter::field_set<
               uint16_t, bitter::lsb0, 1, 8, 8>(temp, 4U);
        EXPECT_EQ(1089U, temp);
    }
    {
        uint16_t temp = 0U;
        temp = bitter::field_set<
               uint16_t, bitter::msb0, 0, 8, 8>(temp, 0xFF);
        EXPECT_EQ(0xFF00, temp);
        temp = bitter::field_set<
               uint16_t, bitter::msb0, 1, 8, 8>(temp, 0xBB);
        EXPECT_EQ(0xFFBB, temp);
    }
}
