// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <bitter/size_in_bits.hpp>

#include <bitter/types.hpp>

#include <cstdint>

#include <gtest/gtest.h>

TEST(test_size_in_bits, u8)
{
    EXPECT_EQ(8U, (bitter::size_in_bits<bitter::u8>()));
}

TEST(test_size_in_bits, u16)
{
    EXPECT_EQ(16U, (bitter::size_in_bits<bitter::u16>()));
}

TEST(test_size_in_bits, u24)
{
    EXPECT_EQ(24U, (bitter::size_in_bits<bitter::u24>()));
}

TEST(test_size_in_bits, u32)
{
    EXPECT_EQ(32U, (bitter::size_in_bits<bitter::u32>()));
}

TEST(test_size_in_bits, u40)
{
    EXPECT_EQ(40U, (bitter::size_in_bits<bitter::u40>()));
}

TEST(test_size_in_bits, u48)
{
    EXPECT_EQ(48U, (bitter::size_in_bits<bitter::u48>()));
}

TEST(test_size_in_bits, u56)
{
    EXPECT_EQ(56U, (bitter::size_in_bits<bitter::u56>()));
}

TEST(test_size_in_bits, u64)
{
    EXPECT_EQ(64U, (bitter::size_in_bits<bitter::u64>()));
}

TEST(test_size_in_bits, uint8)
{
    EXPECT_EQ(8U, (bitter::size_in_bits<uint8_t>()));
}

TEST(test_size_in_bits, uint16)
{
    EXPECT_EQ(16U, (bitter::size_in_bits<uint16_t>()));
}

TEST(test_size_in_bits, uint32)
{
    EXPECT_EQ(32U, (bitter::size_in_bits<uint32_t>()));
}

TEST(test_size_in_bits, uint64)
{
    EXPECT_EQ(64U, (bitter::size_in_bits<uint64_t>()));
}
