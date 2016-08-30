// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <bitter/bitfield_writer.hpp>
#include <cstdint>
#include <vector>
#include <iostream>
#include <gtest/gtest.h>

//#include "../test_helpers.hpp"


TEST(test_bit_writer_big_endian, write_bit)
{
    std::vector<uint8_t> data_vector;
    data_vector.resize(1);

    auto writer = bitter::bitfield_writer<endian::big_endian, 1>(data_vector);
    writer.write_as_vector<0>(true);
    EXPECT_EQ(writer.data()[0], 128U);
}

TEST(test_bit_writer_big_endian, write_bit_1)
{
    std::vector<uint8_t> data_vector;
    data_vector.resize(1);

    auto writer = bitter::bitfield_writer<endian::big_endian,
                                          8>(data_vector);
    uint8_t data = 32U;
    writer.write_as_vector<0>(data);
    EXPECT_EQ(writer.data()[0], 32U);
}


TEST(test_bit_writer_big_endian, write_bit_2)
{
    std::vector<uint8_t> data_vector;
    data_vector.resize(2);

    auto writer = bitter::bitfield_writer<endian::big_endian,
                                          16>(data_vector);
    writer.write_as_vector<0>(2050U);
    EXPECT_EQ(writer.data()[0], 8U);
    EXPECT_EQ(writer.data()[1], 2U);
}


TEST(test_bit_writer_big_endian, write_bit_3)
{
    std::vector<uint8_t> data_vector;
    data_vector.resize(8);

    auto writer = bitter::bitfield_writer<endian::big_endian,
                                          64>(data_vector);
        writer.write_as_vector<0>(323794U);

    EXPECT_EQ(writer.data()[0], 0U);
    EXPECT_EQ(writer.data()[1], 0U);
    EXPECT_EQ(writer.data()[2], 0U);
    EXPECT_EQ(writer.data()[4], 0U);
    EXPECT_EQ(writer.data()[3], 0U);
    EXPECT_EQ(writer.data()[5], 4U);
    EXPECT_EQ(writer.data()[6], 240U);
    EXPECT_EQ(writer.data()[7], 210U);
}

TEST(test_bit_writer_big_endian, write_bit_4)
{
    std::vector<uint8_t> data_vector;
    data_vector.resize(4);

    auto writer = bitter::bitfield_writer<endian::big_endian,
    32>(data_vector);
    writer.write_as_vector<0>(323794U);

    EXPECT_EQ(writer.data()[3], 210U);
    EXPECT_EQ(writer.data()[2], 240U);
    EXPECT_EQ(writer.data()[1], 4U);
    EXPECT_EQ(writer.data()[0], 0U);
}

TEST(test_bit_writer_big_endian, write_multiple_bit_fields_1)
{
    std::vector<uint8_t> data_vector;
    data_vector.resize(2);

    auto writer = bitter::bitfield_writer<endian::big_endian,
                                          1, 8>(data_vector);

    writer.write_as_vector<0>(true);
    EXPECT_EQ(writer.data()[0], 128U);
    writer.write_as_vector<1>(128U);

    EXPECT_EQ(writer.data()[0], 192U);
    EXPECT_EQ(writer.data()[1], 0U);
}

TEST(test_bit_writer_big_endian, write_multiple_bit_fields_2)
{
    std::vector<uint8_t> data_vector;
    data_vector.resize(9);

    auto writer = bitter::bitfield_writer<endian::big_endian,
                                          1, 64>(data_vector);

    writer.write_as_vector<0>(true);
    EXPECT_EQ(writer.data()[0], 128U);
    writer.write_as_vector<1>(64U);

    EXPECT_EQ(writer.data()[0], 128U);
    EXPECT_EQ(writer.data()[1], 0U);
    EXPECT_EQ(writer.data()[2], 0U);
    EXPECT_EQ(writer.data()[3], 0U);
    EXPECT_EQ(writer.data()[4], 0U);
    EXPECT_EQ(writer.data()[5], 0U);
    EXPECT_EQ(writer.data()[6], 0U);
    EXPECT_EQ(writer.data()[7], 32U);
    EXPECT_EQ(writer.data()[8], 0U);
}

TEST(test_bit_writer_big_endian, write_tcp_header)
{
    std::vector<uint8_t> data_vector;
    data_vector.resize(24);
    auto writer = bitter::bitfield_writer<endian::big_endian,
                                          16,16,32,32,
                                          4,6,1,1,
                                          1,1,1,1,
                                          16,16,16,
                                          24,8>(data_vector);
    writer.write_as_vector<0>(128U);
    EXPECT_EQ(writer.data()[0], 0U);
    EXPECT_EQ(writer.data()[1], 128U);
    writer.write_as_vector<1>(255U);
    EXPECT_EQ(writer.data()[2], 0U); // When jump to C++14 is made use 0b11111
    EXPECT_EQ(writer.data()[3], 255U);
    writer.write_as_vector<2>(82000U);
    EXPECT_EQ(writer.data()[4], 0U);
    EXPECT_EQ(writer.data()[5], 1U);
    EXPECT_EQ(writer.data()[6], 64U);
    EXPECT_EQ(writer.data()[7], 80U);
    writer.write_as_vector<3>(4000000U);
    EXPECT_EQ(writer.data()[8], 0U);
    EXPECT_EQ(writer.data()[9], 61U);
    EXPECT_EQ(writer.data()[10], 9U);
    EXPECT_EQ(writer.data()[11], 0U);
    writer.write_as_vector<4>(8U);
    EXPECT_EQ(writer.data()[12], 128U);
    writer.write_as_vector<5>(0U);
    EXPECT_EQ(writer.data()[12], 128U);
    EXPECT_EQ(writer.data()[13], 0U);
    writer.write_as_vector<6>(true);
    EXPECT_EQ(writer.data()[13], 32U);
    writer.write_as_vector<7>(false);
    EXPECT_EQ(writer.data()[13], 32U);
    writer.write_as_vector<8>(true);
    EXPECT_EQ(writer.data()[13], 40U);
    writer.write_as_vector<9>(true);
    EXPECT_EQ(writer.data()[13], 44U);
    writer.write_as_vector<10>(false);
    EXPECT_EQ(writer.data()[13], 44U);
    writer.write_as_vector<11>(true);
    EXPECT_EQ(writer.data()[13], 45U);
    writer.write_as_vector<12>(8192U);
    EXPECT_EQ(writer.data()[14], 32U);
    EXPECT_EQ(writer.data()[15], 0U);
    writer.write_as_vector<13>(12288U);
    EXPECT_EQ(writer.data()[16], 48U);
    EXPECT_EQ(writer.data()[17], 0U);
    writer.write_as_vector<14>(12368U);
    EXPECT_EQ(writer.data()[18], 48U);
    EXPECT_EQ(writer.data()[19], 80U);
    writer.write_as_vector<15>(2097152U);
    EXPECT_EQ(writer.data()[20], 32U);
    EXPECT_EQ(writer.data()[21], 0U);
    EXPECT_EQ(writer.data()[22], 0U);
    EXPECT_EQ(writer.data()[23], 0U);
    writer.write_as_vector<16>(255U);
    EXPECT_EQ(writer.data()[23], 255U);
}
