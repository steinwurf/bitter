// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <bitter/detail/sum_sizes.hpp>

#include <cstdint>

#include <gtest/gtest.h>

TEST(test_sum_sizes, sum_sizes)
{
    EXPECT_EQ(1U, (bitter::sum_sizes<1>()));
}

TEST(test_sum_sizes, sum_sizes1)
{
    EXPECT_EQ(8U, (bitter::sum_sizes<1, 3, 4>()));
}

TEST(test_sum_sizes, sum_sizes2)
{
    EXPECT_EQ(32U, (bitter::sum_sizes<1, 3, 4, 8, 16>()));
}
