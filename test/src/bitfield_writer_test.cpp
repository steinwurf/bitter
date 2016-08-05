#include <bitter/bitfield_writer.hpp>
#include <cstdint>
#include <gtest/gtest.h>

TEST(test_bit_writer, write_bit)
{
    uint8_t* data;
    uint64_t bits = 1;
    auto writer = bitter::bitfield_writer<1>(data, bits);

}
