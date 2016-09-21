// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <bitter/writer.hpp>

#include <cstdint>
#include <vector>
#include <iostream>
#include <gtest/gtest.h>

#include "../test_helpers.hpp"

TEST(test_bit_writer, write_bit)
{

    auto writer = bitter::writer<uint8_t, 1, 7>();
    writer.write<0>(true);
    uint8_t input = 64u;
    writer.write<1>(input);
    auto value = writer.data();
    EXPECT_EQ(value, 129U);
}

TEST(test_bit_writer, write_bit_1)
{
    auto writer = bitter::writer<uint16_t, 16>();
    uint16_t input = 2050U;
    writer.write<0>(input);

    auto value = writer.data();
    EXPECT_EQ(value, 2050U);
}

TEST(test_bit_writer, write_bit_2)
{
    auto writer = bitter::writer<uint32_t, 32>();

    uint32_t input = 323794U;
    writer.write<0>(input);

    auto value = writer.data();
    EXPECT_EQ(value, 323794U);

}

TEST(test_bit_writer, write_bit_3)
{
    auto writer = bitter::writer<uint64_t, 32, 32>();

    uint32_t input = 323794U;
    writer.write<0>(input);
    input = 323694U;
    writer.write<1>(input);
    auto value = writer.data();
    EXPECT_EQ(value, 0x4F06E0004F0D2U);

}


TEST(test_bit_writer, write_bit_4)
{
    auto writer = bitter::writer<uint32_t, 16, 16>();
    uint16_t input = 512U;
    writer.write<0>(input);

    input = 1024U;
    writer.write<1>(input);

    auto value = writer.data();
    EXPECT_EQ(value, 67109376U);
}

TEST(test_bit_writer, write_bit_5)
{
    auto writer = bitter::writer<uint32_t, 8, 8, 8, 8>();
    uint8_t input = 128U;
    writer.write<0>(input);

    input = 255U;
    writer.write<1>(input);

    input = 2U;
    writer.write<2>(input);

    input = 64U;
    writer.write<3>(input);

    auto value = writer.data();
    EXPECT_EQ(value, 1073938304U);
}


// TEST(test_bit_writer, write_bit_4)
// {
//     auto writer = bitter::writer<uint64_t,
//                                           64>();
//
//     uint64_t input = 323794U;
//     writer.write<0>(input);
//
//     uint64_t value = writer.data();
//     EXPECT_EQ(value, 323794U);
//
// }

// TEST(test_bit_writer, write_bit_4)
// {
//     auto writer = bitter::writer<uint32_t, 32>();
//     writer.write<0>(323794U);
//
//     if (is_big_endian)
//     {
//         EXPECT_EQ(writer.data_as_pointer()[3], 0U);
//         EXPECT_EQ(writer.data_as_pointer()[2], 4U);
//         EXPECT_EQ(writer.data_as_pointer()[1], 240U);
//         EXPECT_EQ(writer.data_as_pointer()[0], 210U);
//     }
//     else
//     {
//         EXPECT_EQ(writer.data_as_pointer()[0], 0U);
//         EXPECT_EQ(writer.data_as_pointer()[1], 4U);
//         EXPECT_EQ(writer.data_as_pointer()[2], 240U);
//         EXPECT_EQ(writer.data_as_pointer()[3], 210U);
//     }
// }



// TEST(test_bit_writer, write_multiple_bit_fields_1)
// {
//     std::vector<uint8_t> data_vector;
//     data_vector.resize(2);

//     auto writer = bitter::writer<endian::little_endian,
//                                           1, 8>(data_vector);

//     writer.write_as_vector<0>(true);
//     EXPECT_EQ(writer.data()[0], 128U);
//     writer.write_as_vector<1>(128U);

//     EXPECT_EQ(writer.data()[0], 192U);
//     EXPECT_EQ(writer.data()[1], 0U);
// }

// TEST(test_bit_writer, write_multiple_bit_fields_2)
// {
//     std::vector<uint8_t> data_vector;
//     data_vector.resize(9);

//     auto writer = bitter::writer<endian::little_endian,
//                                           1, 64>(data_vector);

//     writer.write_as_vector<0>(true);
//     EXPECT_EQ(writer.data()[0], 128U);
//     writer.write_as_vector<1>(64U);

//     EXPECT_EQ(writer.data()[0], 128U);
//     EXPECT_EQ(writer.data()[1], 0U);
//     EXPECT_EQ(writer.data()[2], 0U);
//     EXPECT_EQ(writer.data()[3], 0U);
//     EXPECT_EQ(writer.data()[4], 0U);
//     EXPECT_EQ(writer.data()[5], 0U);
//     EXPECT_EQ(writer.data()[6], 0U);
//     EXPECT_EQ(writer.data()[7], 32U);
//     EXPECT_EQ(writer.data()[8], 0U);
// }

TEST(test_bit_writer, write_tcp_header)
{

    auto first_header_row_writer = bitter::writer<uint32_t, 16,16>();
    first_header_row_writer.write<0>(128U);
    first_header_row_writer.write<1>(255U);

    EXPECT_EQ(first_header_row_writer.data(), 0xFF0080U);

    auto second_header_row_writer = bitter::writer<uint32_t, 32>();
    second_header_row_writer.write<0>(82000U);
    EXPECT_EQ(second_header_row_writer.data(), 0x14050U);

    auto third_header_row_writer = bitter::writer<uint32_t, 32>();
    third_header_row_writer.write<0>(4000000U);
    EXPECT_EQ(third_header_row_writer.data(), 0x3D0900U);

    auto fourth_header_row_writer =
        bitter::writer<uint32_t, 4, 6, 1, 1, 1, 1, 1, 1, 16>();
    fourth_header_row_writer.write<0>(8U);
    fourth_header_row_writer.write<1>(0U);
    fourth_header_row_writer.write<2>(true);
    fourth_header_row_writer.write<3>(false);
    fourth_header_row_writer.write<4>(true);
    fourth_header_row_writer.write<5>(true);
    fourth_header_row_writer.write<6>(false);
    fourth_header_row_writer.write<7>(true);
    fourth_header_row_writer.write<8>(8192U);

    EXPECT_EQ(fourth_header_row_writer.data(), 0x2000B408U);

    auto fifth_header_row_writer = bitter::writer<uint32_t, 16, 16>();
    fifth_header_row_writer.write<0>(12288U);
    fifth_header_row_writer.write<1>(12368U);
    EXPECT_EQ(fifth_header_row_writer.data(), 0x30503000U);

    auto sixth_header_row_writer = bitter::writer<uint32_t, 24,8>();
    sixth_header_row_writer.write<0>(2097152U);
    sixth_header_row_writer.write<1>(255U);

    EXPECT_EQ(sixth_header_row_writer.data(), 0xFF200000U);


}
