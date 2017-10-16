// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <bitter/field_mask.hpp>

#include <bitter/types.hpp>

#include <cstdint>

#include <gtest/gtest.h>

TEST(test_field_mask, field_mask)
{

    EXPECT_EQ(0b1U, (bitter::field_mask<bitter::u8, 0, 1, 7>()));
    EXPECT_EQ(0b1111111U, (bitter::field_mask<bitter::u8, 1, 1, 7>()));
}

TEST(test_field_mask, field_mask1)
{

    EXPECT_EQ(0b1U, (bitter::field_mask<bitter::u8, 0, 1, 4, 3>()));
    EXPECT_EQ(0b1111U, (bitter::field_mask<bitter::u8, 1, 1, 4, 3>()));
    EXPECT_EQ(0b111U, (bitter::field_mask<bitter::u8, 2, 1, 4, 3>()));
}

TEST(test_field_mask, field_mask2)
{
    EXPECT_EQ(0xFU, (bitter::field_mask<bitter::u24, 0, 4, 20>()));
    EXPECT_EQ(0xFFFFFU, (bitter::field_mask<bitter::u24, 1, 4, 20>()));
}

TEST(test_field_mask, field_mask3)
{
    EXPECT_EQ(0xFFFFFFU, (bitter::field_mask<bitter::u24, 0, 24>()));
}
