#include <bitter/bitfield_writer.hpp>
#include <cstdint>
#include <vector>
#include <iostream>
#include <gtest/gtest.h>

#include "../test_helpers.hpp"


TEST(test_bit_writer, write_bit)
{
    std::vector<uint8_t> data_vector;
    data_vector.resize(1);

    uint64_t bits = 1;
    auto writer = bitter::bitfield_writer<1>(data_vector, bits);
    writer.write<0, bool>(true);
    std::cout << "/* message */:: " << static_cast<int>(writer.data()[0]) << std::endl;
    EXPECT_EQ(writer.data()[0], 128U);
    //EXPECT_EQ(writer.data()[0], 128U);
}

TEST(test_bit_writer, write_bit_1)
{
    std::vector<uint8_t> data_vector;
    data_vector.resize(1);

    uint64_t bits = 8;
    auto writer = bitter::bitfield_writer<8>(data_vector, bits);
    writer.write<0, uint8_t>(32U);
    EXPECT_EQ(writer.data()[0], 32U);
}


TEST(test_bit_writer, write_bit_2)
{
    std::vector<uint8_t> data_vector;
    data_vector.resize(2);

    uint64_t bits = 16;
    auto writer = bitter::bitfield_writer<16>(data_vector, bits);
    writer.write<0, uint16_t>(2050U);
    EXPECT_EQ(writer.data()[0], 8U);
    EXPECT_EQ(writer.data()[1], 2U);
}

TEST(test_bit_writer, write_bit_4)
{
    std::vector<uint8_t> data_vector;
    data_vector.resize(4);

    uint64_t bits = 32;
    auto writer = bitter::bitfield_writer<32>(data_vector, bits);
    writer.write<0, uint32_t>(323794U);

    EXPECT_EQ(writer.data()[0], 0U);
    EXPECT_EQ(writer.data()[1], 4U);
    EXPECT_EQ(writer.data()[2], 240U);
    EXPECT_EQ(writer.data()[3], 210U);
}

TEST(test_bit_writer, write_bit_3)
{
    std::vector<uint8_t> data_vector;
    data_vector.resize(8);

    uint64_t bits = 64;
    auto writer = bitter::bitfield_writer<64>(data_vector, bits);
    writer.write<0, uint32_t>(323794U);

    EXPECT_EQ(writer.data()[0], 0U);
    EXPECT_EQ(writer.data()[1], 4U);
    EXPECT_EQ(writer.data()[2], 240U);
    EXPECT_EQ(writer.data()[3], 210U);
    EXPECT_EQ(writer.data()[4], 0U);
    EXPECT_EQ(writer.data()[5], 0U);
    EXPECT_EQ(writer.data()[6], 0U);
    EXPECT_EQ(writer.data()[7], 0U);
}

TEST(test_bit_writer, write_multiple_bit_fields_1)
{
    std::vector<uint8_t> data_vector;
    data_vector.resize(2);

    uint64_t bits = 9;
    auto writer = bitter::bitfield_writer<1, 8>(data_vector, bits);

    writer.write<0, bool>(true);
    EXPECT_EQ(writer.data()[0], 128U);
    writer.write<1, uint64_t>(128U);

    EXPECT_EQ(writer.data()[0], 192U);
    EXPECT_EQ(writer.data()[1], 0U);
}

TEST(test_bit_writer, write_multiple_bit_fields_2)
{
    std::vector<uint8_t> data_vector;
    data_vector.resize(9);

    uint64_t bits = 65;
    auto writer = bitter::bitfield_writer<1, 64>(data_vector, bits);

    writer.write<0, bool>(true);
    EXPECT_EQ(writer.data()[0], 128U);
    writer.write<1, uint64_t>(64U);

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
