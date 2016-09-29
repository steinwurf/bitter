// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <bitter/field_set.hpp>

#include <cstdint>

#include <gtest/gtest.h>

TEST(test_field_set, field_set)
{
    uint16_t temp = 0U;
    temp = bitter::field_set<uint16_t, 0, 8, 8>(temp, 65U);
    EXPECT_EQ(65U, temp);
    temp = bitter::field_set<uint16_t, 1, 8, 8>(temp, 4U);
    EXPECT_EQ(1089U, temp);
}
