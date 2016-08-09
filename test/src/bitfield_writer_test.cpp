#include <bitter/bitfield_writer.hpp>
#include <cstdint>
#include <vector>
#include <iostream>
#include <gtest/gtest.h>


TEST(test_bit_writer, write_bit)
{
    std::vector<uint8_t> data_vector(1);

    uint64_t bits = 1;
    auto writer = bitter::bitfield_writer<1>(data_vector.data(), bits);
        writer.write<0, bool>(true);
    EXPECT_EQ(writer.data()[0], 128U);
}

TEST(test_bit_writer, write_bit_1)
{
    std::vector<uint8_t> data_vector(1);

    uint64_t bits = 8;
    auto writer = bitter::bitfield_writer<8>(data_vector.data(), bits);
        writer.write<0, uint8_t>(32U);
    EXPECT_EQ(writer.data()[0], 32U);
}
