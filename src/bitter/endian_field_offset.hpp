// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include <cstdint>
#include <type_traits>

#include "lsb0.hpp"
#include "msb0.hpp"
#include "size_in_bits.hpp"
#include "field_offset.hpp"
#include "sum_sizes.hpp"

namespace bitter
{








///   bitter::field<uint32_t, msb0, 4, 4, 8, 16>



/// Bit numbering modes (also sometimes called endianess), say we have a
/// single byte (8 bits):
///
///      least significant +--------+
///      bit                        |
///                                 v
///   +-------------------------------+
///   | 0   1   0   1   1   1   0   0 |
///   +-------------------------------+
///     ^
///     |             most significant
///     +-----------+ bit
///
/// There are two common ways we can number the bits inside the byte (from
/// https://en.wikipedia.org/wiki/Bit_numbering):
///
/// 1. MSB 0 bit numbering:
///    When the bit numbering starts at zero for the most significant bit
///    (MSB) the numbering scheme is called "MSB 0".
///
/// 2. LSB 0 bit numbering
///    When the bit numbering starts at zero for the least significant bit
///    (LSB) the numbering scheme is called "LSB 0".
///
/// Lets number the bits inside byte given earlier according to the LSB 0
/// bit numbering.
///
///     7   6   5   4   3   2   1   0
///   +-------------------------------+
///   | 0   1   0   1   1   1   0   0 |
///   +-------------------------------+
///
/// This numbering scheme is the one we typically use when working with
/// binary numbers and when programming. E.g. to access bit at index 2 we
/// have to perform 2 right shifts.
///
/// On the other hand if we use MSB 0 bit numbering we have the most
/// significant bit numberd zero. This is typically used in RFCs because
/// it makes it possible to draw a protocol with bit numbering running
/// consecutively over a multi-byte value written in big endian.
///
/// For example take the first part of the IPv4 header
/// (https://en.wikipedia.org/wiki/IPv4). The IPv4 header is MSB 0
/// numbered.
///
///  There are four bytes (32 bits) in the first chunk of the header. This
///  is written to the wire in big endian format (most significant byte)
///  first. As can be seen this is consistent with MSB 0 bit numbering
///  since bit 0 is the most significant bit.
///
///    0                   1                   2                   3
///    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
///   +---------------------------------------------------------------+
///   |Version|  IHL  |Type of Service|          Total Length         |
///   +---------------------------------------------------------------+
///
/// Lets look at how we work with this in bitter. In bitter the fields
/// layed out from bit number 0.
///
/// So imagine we have the following bit reader:
///
///     auto reader = bitter::lsb_reader<uint8_t, 1, 2, 3, 2>(0xdeadbeef);
///
/// We have four fields of size 1, 2, 3, 2 bits respectively (8 bits in
/// total). We use the lsb_reader to use LSB 0 bit numbering so we have
/// the following layout of the four fields inside the byte:
///
///     7   6   5   4   3   2   1   0
///   +-------+-----------+-------+---+
///   | 0   1 | 0   1   1 | 1   0 | 0 |
///   +-------+-----------+-------+---+
///                                 ^
///                                 |
///      least significant +--------+
///      bit
///
///
/// So the first field is at bit 0 which is the lest significant bit
/// inside the byte.
///
/// If on the other had we use the msb_reader the example would be:
///
///     auto reader = bitter::msb_reader<uint8_t, 1, 2, 3, 2>(0xdeadbeef);
///
/// We would have the following layout of the four fields inside the byte:
///
///     0   1   2   3   4   5   6   7
///   +---+-------+-----------+-------+
///   | 0 | 1   0 | 1   1   1 | 0   0 |
///   +---+-------+-----------+-------+
///     ^
///     |             most significant
///     +-----------+ bit


namespace detail
{


template<uint32_t Index, uint32_t Counter, uint32_t Size0>
uint32_t help_msb_field_offset()
{
    static_assert(Index == Counter, "");
    return 0;
}

template<uint32_t Index, uint32_t Counter, uint32_t Size0, uint32_t Size1, uint32_t... Sizes>
uint32_t help_msb_field_offset()
{
    if (Index == Counter)
    {
        return sum_sizes<Size1, Sizes...>();
    }
    else
    {
        return help_msb_field_offset<Index, Counter + (Counter < Index ? 1 : 0), Size1, Sizes...>();
    }
}

}

template<uint32_t Index, uint32_t... Sizes>
uint32_t msb_field_offset()
{
    return detail::help_msb_field_offset<Index, 0, Sizes...>();
}


}
