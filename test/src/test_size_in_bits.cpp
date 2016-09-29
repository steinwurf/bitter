// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <bitter/size_in_bits.hpp>

#include <cstdint>

#include <gtest/gtest.h>

TEST(test_size_in_bits, field_size_in_bits)
{
    EXPECT_EQ(1U, (bitter::size_in_bits<bool>()));
}

TEST(test_size_in_bits, field_size_in_bits1)
{
    EXPECT_EQ(8U, (bitter::size_in_bits<uint8_t>()));
}

TEST(test_size_in_bits, field_size_in_bits2)
{
    EXPECT_EQ(16U, (bitter::size_in_bits<uint16_t>()));
}

TEST(test_size_in_bits, field_size_in_bits3)
{
    EXPECT_EQ(32U, (bitter::size_in_bits<uint32_t>()));
}

TEST(test_size_in_bits, field_size_in_bits4)
{
    EXPECT_EQ(64U, (bitter::size_in_bits<uint64_t>()));
}
