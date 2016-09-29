// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <bitter/field_mask.hpp>

#include <cstdint>

#include <gtest/gtest.h>

TEST(test_field_mask, field_mask)
{

    EXPECT_EQ(1U, (bitter::field_mask<uint8_t, 0, 1, 7>()));
    EXPECT_EQ(127U, (bitter::field_mask<uint8_t, 1, 1, 7>()));
}

TEST(test_field_mask, field_mask1)
{

    EXPECT_EQ(1U, (bitter::field_mask<uint8_t, 0, 1, 4, 3>()));
    EXPECT_EQ(15U, (bitter::field_mask<uint8_t, 1, 1, 4, 3>()));
    EXPECT_EQ(7U, (bitter::field_mask<uint8_t, 2, 1, 4, 3>()));
}
