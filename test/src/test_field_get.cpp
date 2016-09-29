// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <bitter/field_get.hpp>

#include <cstdint>

#include <gtest/gtest.h>

TEST(test_field_get, field)
{
    uint8_t value = 255U;
    EXPECT_TRUE(((bool)bitter::field_get<uint8_t, 0, 1, 7>(value)));
    EXPECT_EQ(127U, (bitter::field_get<uint8_t, 1, 1, 7>(value)));
}

TEST(test_field_get, field1)
{
    uint8_t value = 255U;
    EXPECT_EQ(1U, (bitter::field_get<uint8_t, 0, 1, 7>(value)));
    EXPECT_EQ(127U, (bitter::field_get<uint8_t, 1, 1, 7>(value)));
}

TEST(test_field_get, field2)
{
    uint16_t value = 1024U;
    EXPECT_EQ(0U, (bitter::field_get<uint16_t, 0, 8, 8>(value)));
    EXPECT_EQ(4U, (bitter::field_get<uint16_t, 1, 8, 8>(value)));
}
