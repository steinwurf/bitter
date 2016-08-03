#include <bitter/bitfield_reader.hpp>

#include <cstdint>

#include <gtest/gtest.h>

TEST(test_bit_reader, read_bit)
{
    std::vector<uint8_t> data
    {
        0x00, //0000 0000
        0xFF, //1111 1111
        0xF0, //1111 0000
        0x0F, //0000 1111
        0xA5, //1010 0101
    };

    auto reader =
         bitter::bitfield_reader<8,8,8,8,8>(data.data(), data.size() * 8);

    // Test that groups have correct offset
    EXPECT_EQ(0U, reader.offset<0>());
    EXPECT_EQ(8U, reader.offset<1>());
    EXPECT_EQ(16U, reader.offset<2>());
    EXPECT_EQ(24U, reader.offset<3>());
    EXPECT_EQ(32U, reader.offset<4>());

    // Test that groups have correct size
    EXPECT_EQ(8U, reader.group_size<0>());
    EXPECT_EQ(8U, reader.group_size<1>());
    EXPECT_EQ(8U, reader.group_size<2>());
    EXPECT_EQ(8U, reader.group_size<3>());
    EXPECT_EQ(8U, reader.group_size<4>());

    auto value = reader.get<uint8_t, 0>();
    EXPECT_EQ(0U, value);

    value = reader.get<uint8_t, 1>();
    EXPECT_EQ(255U, value);

    value = reader.get<uint8_t, 2>();
    EXPECT_EQ(240U, value);

    value = reader.get<uint8_t, 3>();
    EXPECT_EQ(15U, value);

    value = reader.get<uint8_t, 4>();
    EXPECT_EQ(165U, value);
}
