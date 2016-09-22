// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <bitter/field_get.hpp>

#include <cstdint>

#include <gtest/gtest.h>

TEST(test_field_get, field)
{
    uint8_t value = 255;
    EXPECT_TRUE((bitter::field_get<bool, 0, 1, 7>(value)));
    EXPECT_EQ(127U, (bitter::field_get<uint8_t, 1, 1, 7>(value)));
}
