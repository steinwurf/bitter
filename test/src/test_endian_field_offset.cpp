// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <bitter/endian_field_offset.hpp>

#include <cstdint>

#include <gtest/gtest.h>

TEST(test_endian_field_offset, field_offset_index0_lsb0)
{
    uint32_t offset = bitter::endian_field_offset<uint16_t, 0, 1, 4, 6, 5>(
        bitter::lsb0());
    EXPECT_EQ(0U, offset);
}

TEST(test_endian_field_offset, field_offset_index0_msb0)
{
    uint32_t offset = bitter::endian_field_offset<uint16_t, 0, 1, 4, 6, 5>(
        bitter::msb0());
    EXPECT_EQ(15U, offset);
}

TEST(test_endian_field_offset, field_offset_index1_lsb0)
{
    uint32_t offset = bitter::endian_field_offset<uint16_t, 1, 1, 4, 6, 5>(
        bitter::lsb0());
    EXPECT_EQ(1U, offset);
}

TEST(test_endian_field_offset, field_offset_index1_msb0)
{
    uint32_t offset = bitter::endian_field_offset<uint16_t, 1, 1, 4, 6, 5>(
        bitter::msb0());
    EXPECT_EQ(14U, offset);
}

TEST(test_endian_field_offset, field_offset_index2_lsb0)
{
    uint32_t offset = bitter::endian_field_offset<uint16_t, 2, 1, 4, 6, 5>(
        bitter::lsb0());
    EXPECT_EQ(5U, offset);
}

TEST(test_endian_field_offset, field_offset_index2_msb0)
{
    uint32_t offset = bitter::endian_field_offset<uint16_t, 2, 1, 4, 6, 5>(
        bitter::msb0());
    EXPECT_EQ(10U, offset);
}

TEST(test_endian_field_offset, field_offset_index3_lsb0)
{
    uint32_t offset = bitter::endian_field_offset<uint16_t, 3, 1, 4, 6, 5>(
        bitter::lsb0());
    EXPECT_EQ(11U, offset);
}

TEST(test_endian_field_offset, field_offset_index3_msb0)
{
    uint32_t offset = bitter::endian_field_offset<uint16_t, 3, 1, 4, 6, 5>(
        bitter::msb0());
    EXPECT_EQ(0U, offset);
}
//
// TEST(test_field_offset, field_offset2)
// {
//     EXPECT_EQ(1U, (bitter::field_offset<1, 1, 4, 6, 5>()));
// }
//
// TEST(test_field_offset, field_offset3)
// {
//     EXPECT_EQ(5U, (bitter::field_offset<2, 1, 4, 6, 5>()));
// }
//
// TEST(test_field_offset, field_offset4)
// {
//     EXPECT_EQ(11U, (bitter::field_offset<3, 1, 4, 6, 5>()));
// }
