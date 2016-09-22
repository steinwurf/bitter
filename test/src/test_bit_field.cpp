// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <bitter/bit_field.hpp>

#include <cstdint>

#include <gtest/gtest.h>

TEST(test_bit_field, bit_field_read_as)
{

    auto field = bitter::bit_field<uint8_t>(1U, 1U);
    EXPECT_TRUE(field.read_as<bool>());
}

TEST(test_bit_field, bit_field_read_as1)
{
    auto field = bitter::bit_field<uint8_t>(0U, 1U);
    EXPECT_FALSE(field.read_as<bool>());
}

TEST(test_bit_field, bit_field_read_as2)
{
    auto field = bitter::bit_field<uint8_t>(255U, 8U);
    EXPECT_EQ(255U, field.read_as<uint8_t>());
}
