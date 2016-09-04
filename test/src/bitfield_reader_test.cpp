// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file
#include <bitter/bitfield_reader.hpp>

#include <endian/is_big_endian.hpp>
#include <endian/big_endian.hpp>
#include <endian/little_endian.hpp>

#include <cstdint>

#include <gtest/gtest.h>

#include <typeinfo>

bool is_test_big_endian = endian::is_big_endian();

TEST(test_bit_reader, read_bit)
{

    uint32_t input = 0x0FF0FF00U;


    auto reader =
        bitter::bitfield_reader<uint32_t, 8,8,8,8>(input);

    if(is_test_big_endian)
    {

        EXPECT_EQ(reader.data_ptr()[3], 0U);
        EXPECT_EQ(reader.data_ptr()[2], 255U);
        EXPECT_EQ(reader.data_ptr()[1], 240U);
        EXPECT_EQ(reader.data_ptr()[0], 15U);
        reader.convert_endianness<endian::little_endian>();
        std::cout << "testing that test is run" << std::endl;
        EXPECT_EQ(reader.data_ptr()[0], 0U);
        EXPECT_EQ(reader.data_ptr()[1], 255U);
        EXPECT_EQ(reader.data_ptr()[2], 240U);
        EXPECT_EQ(reader.data_ptr()[3], 15U);
    }
    else
    {
        EXPECT_EQ(reader.data_ptr()[0], 0U);
        EXPECT_EQ(reader.data_ptr()[1], 255U);
        EXPECT_EQ(reader.data_ptr()[2], 240U);
        EXPECT_EQ(reader.data_ptr()[3], 15U);
    }



    // auto value = reader.read<uint8_t, 0>();
    // EXPECT_EQ(0U, value);

    // value = reader.read<uint8_t, 1>();
    // EXPECT_EQ(255U, value);

    // value = reader.read<uint8_t, 2>();
    // EXPECT_EQ(240U, value);

    // value = reader.read<uint8_t, 3>();xo
    // EXPECT_EQ(15U, value);

}

// TEST(test_bit_reader, read_bit2)
// {
//     std::vector<uint8_t> data
//     {
//         0x00, //0000 0000
//         0xFF, //1111 1111
//         0xF0, //1111 0000
//         0x0F, //0000 1111
//         0xA5, //1010 0101
//         0xF0, //1111 0000
//     };

//     auto reader =
//          bitter::bitfield_reader<endian::little_endian, 16,16,16>(data);

//     // Test that groups have correct offset
//     EXPECT_EQ(0U, reader.offset<0>());
//     EXPECT_EQ(16U, reader.offset<1>());
//     EXPECT_EQ(32U, reader.offset<2>());

//     // Test that groups have correct size
//     EXPECT_EQ(16U, reader.group_size<0>());
//     EXPECT_EQ(16U, reader.group_size<1>());
//     EXPECT_EQ(16U, reader.group_size<2>());

//     auto value = reader.read<uint16_t, 0>();
//     EXPECT_EQ(65280U, value);

//     value = reader.read<uint16_t, 1>();
//     EXPECT_EQ(61455U, value);

//     value = reader.read<uint16_t, 2>();
//     EXPECT_EQ(42480U, value);
// }

// TEST(test_bit_reader, read_bit3)
// {
//     std::vector<uint8_t> data
//     {
//         0x00, //0000 0000
//         0xFF, //1111 1111
//         0xF0, //1111 0000
//         0x0F, //0000 1111
//         0xA5, //1010 0101
//         0xF0, //1111 0000
//         0x0F, //0000 1111
//         0xA5, //1010 0101
//     };

//     auto reader =
//          bitter::bitfield_reader<endian::little_endian, 32,32>(data);

//     // Test that groups have correct offset
//     EXPECT_EQ(0U, reader.offset<0>());
//     EXPECT_EQ(32U, reader.offset<1>());

//     // Test that groups have correct size
//     EXPECT_EQ(32U, reader.group_size<0>());
//     EXPECT_EQ(32U, reader.group_size<1>());

//     auto value = reader.read<uint32_t, 0>();
//     EXPECT_EQ(16773135U, value);

//     value = reader.read<uint32_t, 1>();
//     EXPECT_EQ(2783973285U, value);
// }

// TEST(test_bit_reader, read_bit4)
// {
//     std::vector<uint8_t> data
//     {
//         0x00, //0000 0000
//         0xFF, //1111 1111
//         0xF0, //1111 0000
//         0x0F, //0000 1111
//         0xA5, //1010 0101
//         0xF0, //1111 0000
//         0x0F, //0000 1111
//         0xA5, //1010 0101
//     };

//     auto reader =
//          bitter::bitfield_reader<endian::little_endian, 64>(data);

//     // Test that groups have correct offset
//     EXPECT_EQ(0U, reader.offset<0>());

//     // Test that groups have correct size
//     EXPECT_EQ(64U, reader.group_size<0>());
//     //
//     //
//     auto value = reader.read<uint64_t, 0>();
//     EXPECT_EQ(72040069060366245U, value);
// }

// TEST(test_bit_reader, read_bit5)
// {
//     std::vector<uint8_t> data
//     {
//         0xA0, //1010 0000
//     };

//     auto reader =
//          bitter::bitfield_reader<endian::little_endian, 1>(data);

//     // Test that groups have correct offset
//     EXPECT_EQ(0U, reader.offset<0>());

//     // Test that groups have correct size
//     EXPECT_EQ(1U, reader.group_size<0>());

//     auto value = reader.read<bool, 0>();
//     EXPECT_TRUE(value);
// }

// TEST(test_bit_reader, read_bit6)
// {
//     std::vector<uint8_t> data
//     {
//         0x00, //0000 0000
//     };

//     auto reader =
//          bitter::bitfield_reader<endian::little_endian, 1>(data);

//     // Test that groups have correct offset
//     EXPECT_EQ(0U, reader.offset<0>());

//     // Test that groups have correct size
//     EXPECT_EQ(1U, reader.group_size<0>());

//     auto value = reader.read<bool, 0>();
//     EXPECT_FALSE(value);
// }
