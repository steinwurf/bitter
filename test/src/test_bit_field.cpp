// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <bitter/bit_field.hpp>

#include <cstdint>

#include <gtest/gtest.h>

TEST(test_bit_field, bit_field_read_as)
{

    auto field = bitter::bit_field<uint8_t, 1U>(1U);
    EXPECT_TRUE(field.as<bool>());
}

TEST(test_bit_field, bit_field_read_as1)
{
    auto field = bitter::bit_field<uint8_t, 1U>(0U);
    EXPECT_FALSE(field.as<bool>());
}

TEST(test_bit_field, bit_field_read_as2)
{
    auto field = bitter::bit_field<uint8_t, 8U>(255U);
    EXPECT_EQ(255U, field.as<uint8_t>());
}
