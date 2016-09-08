// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <bitter/bitfield_writer.hpp>

#include <endian/is_big_endian.hpp>

#include <cstdint>
#include <vector>
#include <iostream>
#include <gtest/gtest.h>

#include "../test_helpers.hpp"

TEST(test_bit_writer_little_endian, write_bit)
{

    auto writer = bitter::bitfield_writer<uint8_t, 1>();
    writer.write<0>(true);
    auto value = writer.data();

    uint8_t* demo = (uint8_t*) &value;
    print_byte(demo[0]);
    EXPECT_EQ(value, 1U);
}

TEST(test_bit_writer_little_endian, write_bit1)
{

    auto writer = bitter::bitfield_writer<uint8_t, 1, 7>();
    writer.write<0>(true);
    uint8_t input = 64u;
    writer.write<1>(input);
    auto value = writer.data();

    uint8_t* demo = (uint8_t*) &value;
    print_byte(demo[0]);
    EXPECT_EQ(value, 129U);
}

TEST(test_bit_writer_little_endian, write_bit_2)
{
    auto writer = bitter::bitfield_writer<uint16_t,
    16>();
    uint16_t input = 2050U;
    writer.write<0>(input);

    auto value = writer.data();
    EXPECT_EQ(value, 2050U);
}

// TEST(test_bit_writer_little_endian, write_bit)
// {
//
//     auto writer = bitter::bitfield_writer<uint8_t, 1>();
//     writer.write<0>(true);
//     // EXPECT_EQ(writer.data_as_pointer()[0], 1U);  // Will fail till bug is fixed
//     // EXPECT_EQ(writer.data(), 1U); // Will fail till bug is fixed
//     EXPECT_EQ(writer.data_as_pointer()[0], 128U);
//     EXPECT_EQ(writer.data(), 128U);
// }
//
// TEST(test_bit_writer_little_endian, write_bit_1)
// {
//     auto writer = bitter::bitfield_writer<uint8_t,
//                                           8>();
//     writer.write<0>(32U);
//     EXPECT_EQ(writer.data(), 32U);
// }
//
//
//
// TEST(test_bit_writer_little_endian, write_bit_4)
// {
//     auto writer = bitter::bitfield_writer<uint32_t, 32>();
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
//
// TEST(test_bit_writer_little_endian, write_bit_3)
// {
//     auto writer = bitter::bitfield_writer<uint64_t,
//                                           64>();
//     writer.write<0>(323794U);
//
//     if (is_big_endian)
//     {
//         EXPECT_EQ(writer.data_as_pointer()[7], 0U);
//         EXPECT_EQ(writer.data_as_pointer()[6], 0U);
//         EXPECT_EQ(writer.data_as_pointer()[5], 0U);
//         EXPECT_EQ(writer.data_as_pointer()[4], 0U);
//         EXPECT_EQ(writer.data_as_pointer()[3], 0U);
//         EXPECT_EQ(writer.data_as_pointer()[2], 4U);
//         EXPECT_EQ(writer.data_as_pointer()[1], 240U);
//         EXPECT_EQ(writer.data_as_pointer()[0], 210U);
//     }
//     else
//     {
//         EXPECT_EQ(writer.data_as_pointer()[0], 0U);
//         EXPECT_EQ(writer.data_as_pointer()[1], 0U);
//         EXPECT_EQ(writer.data_as_pointer()[2], 0U);
//         EXPECT_EQ(writer.data_as_pointer()[3], 0U);
//         EXPECT_EQ(writer.data_as_pointer()[4], 0U);
//         EXPECT_EQ(writer.data_as_pointer()[5], 4U);
//         EXPECT_EQ(writer.data_as_pointer()[6], 240U);
//         EXPECT_EQ(writer.data_as_pointer()[7], 210U);
//     }
// }


// TEST(test_bit_writer_little_endian, write_multiple_bit_fields_1)
// {
//     std::vector<uint8_t> data_vector;
//     data_vector.resize(2);

//     auto writer = bitter::bitfield_writer<endian::little_endian,
//                                           1, 8>(data_vector);

//     writer.write_as_vector<0>(true);
//     EXPECT_EQ(writer.data()[0], 128U);
//     writer.write_as_vector<1>(128U);

//     EXPECT_EQ(writer.data()[0], 192U);
//     EXPECT_EQ(writer.data()[1], 0U);
// }

// TEST(test_bit_writer_little_endian, write_multiple_bit_fields_2)
// {
//     std::vector<uint8_t> data_vector;
//     data_vector.resize(9);

//     auto writer = bitter::bitfield_writer<endian::little_endian,
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

// TEST(test_bit_writer_little_endian, write_tcp_header)
// {
//     std::vector<uint8_t> data_vector;
//     data_vector.resize(24);
//     auto writer = bitter::bitfield_writer<endian::little_endian,
//                                           16,16,32,32,
//                                           4,6,1,1,
//                                           1,1,1,1,
//                                           16,16,16,
//                                           24,8>(data_vector);
//     writer.write_as_vector<0>(128U);
//     EXPECT_EQ(writer.data()[1], 0U);
//     EXPECT_EQ(writer.data()[0], 128U);
//     writer.write_as_vector<1>(255U);
//     EXPECT_EQ(writer.data()[3], 0U); // When jump to C++14 is made use 0b11111
//     EXPECT_EQ(writer.data()[2], 255U);
//     writer.write_as_vector<2>(82000U);
//     EXPECT_EQ(writer.data()[7], 0U);
//     EXPECT_EQ(writer.data()[6], 1U);
//     EXPECT_EQ(writer.data()[5], 64U);
//     EXPECT_EQ(writer.data()[4], 80U);
//     writer.write_as_vector<3>(4000000U);
//     EXPECT_EQ(writer.data()[11], 0U);
//     EXPECT_EQ(writer.data()[10], 61U);
//     EXPECT_EQ(writer.data()[9], 9U);
//     EXPECT_EQ(writer.data()[8], 0U);
//     writer.write_as_vector<4>(8U);
//     EXPECT_EQ(writer.data()[12], 128U);
//     writer.write_as_vector<5>(0U);
//     EXPECT_EQ(writer.data()[12], 128U);
//     EXPECT_EQ(writer.data()[13], 0U);
//     writer.write_as_vector<6>(true);
//     EXPECT_EQ(writer.data()[13], 32U);
//     writer.write_as_vector<7>(false);
//     EXPECT_EQ(writer.data()[13], 32U);
//     writer.write_as_vector<8>(true);
//     EXPECT_EQ(writer.data()[13], 40U);
//     writer.write_as_vector<9>(true);
//     EXPECT_EQ(writer.data()[13], 44U);
//     writer.write_as_vector<10>(false);
//     EXPECT_EQ(writer.data()[13], 44U);
//     writer.write_as_vector<11>(true);
//     EXPECT_EQ(writer.data()[13], 45U);
//     writer.write_as_vector<12>(8192U);
//     EXPECT_EQ(writer.data()[15], 32U);
//     EXPECT_EQ(writer.data()[14], 0U);
//     writer.write_as_vector<13>(12288U);
//     EXPECT_EQ(writer.data()[17], 48U);
//     EXPECT_EQ(writer.data()[16], 0U);
//     writer.write_as_vector<14>(12368U);
//     EXPECT_EQ(writer.data()[19], 48U);
//     EXPECT_EQ(writer.data()[18], 80U);
//     writer.write_as_vector<15>(2097152U);
//     EXPECT_EQ(writer.data()[23], 32U);
//     EXPECT_EQ(writer.data()[22], 0U);
//     EXPECT_EQ(writer.data()[21], 0U);
//     EXPECT_EQ(writer.data()[20], 0U);
//     writer.write_as_vector<16>(255U);
//     EXPECT_EQ(writer.data()[23], 255U);
// }
