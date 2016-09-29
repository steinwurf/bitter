// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <bitter/field_size_in_bits.hpp>

#include <cstdint>

#include <gtest/gtest.h>

TEST(test_field_size_in_bits, field_size_in_bits)
{
    EXPECT_EQ(8U, (bitter::field_size_in_bits<0, 8, 16, 1, 32, 64>()));
    EXPECT_EQ(16U, (bitter::field_size_in_bits<1, 8, 16, 1, 32, 64>()));
    EXPECT_EQ(1U, (bitter::field_size_in_bits<2, 8, 16, 1, 32, 64>()));
    EXPECT_EQ(32U, (bitter::field_size_in_bits<3, 8, 16, 1, 32, 64>()));
    EXPECT_EQ(64U, (bitter::field_size_in_bits<4, 8, 16, 1, 32, 64>()));
}
