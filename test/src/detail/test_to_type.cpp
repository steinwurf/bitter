// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <bitter/detail/to_type.hpp>

#include <cstdint>

#include <gtest/gtest.h>

// Small Helper
template <class DataType, class BitterType>
using same = std::is_same<bitter::to_type<DataType>, BitterType>;

TEST(test_to_type, to_type)
{
    EXPECT_TRUE((same<uint8_t, bitter::u8>::value));
    EXPECT_TRUE((same<uint16_t, bitter::u16>::value));
    EXPECT_TRUE((same<uint32_t, bitter::u32>::value));
    EXPECT_TRUE((same<uint64_t, bitter::u64>::value));

    EXPECT_TRUE((same<bitter::u8, bitter::u8>::value));
    EXPECT_TRUE((same<bitter::u16, bitter::u16>::value));
    EXPECT_TRUE((same<bitter::u24, bitter::u24>::value));
    EXPECT_TRUE((same<bitter::u32, bitter::u32>::value));
    EXPECT_TRUE((same<bitter::u40, bitter::u40>::value));
    EXPECT_TRUE((same<bitter::u48, bitter::u48>::value));
    EXPECT_TRUE((same<bitter::u56, bitter::u56>::value));
    EXPECT_TRUE((same<bitter::u64, bitter::u64>::value));
}
