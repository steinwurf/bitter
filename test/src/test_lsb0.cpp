// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <bitter/lsb0.hpp>

#include <cstdint>

#include <gtest/gtest.h>

TEST(test_field_offset, field_offset)
{
    EXPECT_EQ(0U, (bitter::lsb0::field_offset<0, 1, 4, 6, 5>()));
}

TEST(test_field_offset, field_offset2)
{
    EXPECT_EQ(1U, (bitter::lsb0::field_offset<1, 1, 4, 6, 5>()));
}

TEST(test_field_offset, field_offset3)
{
    EXPECT_EQ(5U, (bitter::lsb0::field_offset<2, 1, 4, 6, 5>()));
}

TEST(test_field_offset, field_offset4)
{
    EXPECT_EQ(11U, (bitter::lsb0::field_offset<3, 1, 4, 6, 5>()));
}
