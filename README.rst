======
Bitter
======

Is a lightweight Header only C++ API, for reading and writing single bit and
varying length byte fields.

Writing a bit field
-------------------

Lets say we want to write the four bytes of a 32 bit integer individually::

    // Using an uint32_t data type divided into 4 bit fields each 8 bits in
    // size. The sum of the bit fields must match the number of bits in the data
    // type.
    auto writer = bitter::writer<uint32_t, 8, 8, 8, 8>();

    writer.field<0>(0xef); // Write bits 0-7
    writer.field<1>(0xbe); // Write bits 8-15
    writer.field<2>(0xad); // Write bits 16-23
    writer.field<3>(0xde); // Write bits 24-31

    assert(writer.data() == 0xdeadbeef);

Use `#include <bitter/writer.hpp>` to use the `bitter::writer`.

Reading a bit field
-------------------

Given a value we can also read the individual bit fields. Based on the example
above lets read back the four bit fields from the uint32_t value::

    auto reader = bitter::reader<uint32_t, 8, 8, 8, 8>(0xdeadbeef);

    uint8_t value0 = reader.field<0>().read_as<uint8_t>(); // Read bits 0-7
    uint8_t value1 = reader.field<1>().read_as<uint8_t>(); // Read bits 8-15
    uint8_t value2 = reader.field<2>().read_as<uint8_t>(); // Read bits 16-23
    uint8_t value3 = reader.field<3>().read_as<uint8_t>(); // Read bits 24-31

    assert(value0 == 0xef);
    assert(value1 == 0xbe);
    assert(value2 == 0xad);
    assert(value3 == 0xde);

Use `#include <bitter/reader.hpp>` to use the `bitter::reader`.

Bit numbering (bit endianness)
------------------------------

Bit numbering modes (also sometimes called endianess), say we have a
single byte (8 bits)::

       least significant +--------+
       bit                        |
                                  v
    +-------------------------------+
    | 0   1   0   1   1   1   0   0 |
    +-------------------------------+
      ^
      |             most significant
      +-----------+ bit

There are two common ways we can number the bits inside the byte (from
https://en.wikipedia.org/wiki/Bit_numbering):

1. MSB 0 bit numbering:
   When the bit numbering starts at zero for the most significant bit
   (MSB) the numbering scheme is called "MSB 0".
2. LSB 0 bit numbering
   When the bit numbering starts at zero for the least significant bit
   (LSB) the numbering scheme is called "LSB 0".

Lets number the bits inside byte given earlier according to the LSB 0
bit numbering::

      7   6   5   4   3   2   1   0
    +-------------------------------+
    | 0   1   0   1   1   1   0   0 |
    +-------------------------------+

This numbering scheme is the one we typically use when working with
binary numbers and when programming. E.g. to access bit at index 2 we
have to perform 2 right shifts.

On the other hand if we use MSB 0 bit numbering we have the most
significant bit numbered zero. This is typically used in RFCs because
it makes it possible to draw a protocol with bit numbering running
consecutively over a multi-byte value written in big endian.

For example take the first part of the IPv4 header
(https://en.wikipedia.org/wiki/IPv4). The IPv4 header is MSB 0
numbered.

There are four bytes (32 bits) in the first chunk of the header. This
is written to the wire in big endian format (most significant byte)
first. As can be seen this is consistent with MSB 0 bit numbering
since bit 0 is the most significant bit::

     0                   1                   2                   3
     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
    +---------------------------------------------------------------+
    |Version|  IHL  |Type of Service|          Total Length         |
    +---------------------------------------------------------------+

Lets look at how we work with this in bitter. In bitter the fields
laid out from bit number 0.

So imagine we have the following bit reader::

    auto reader = bitter::lsb_reader<uint8_t, 1, 2, 3, 2>(0xdeadbeef);

We have four fields of size 1, 2, 3, 2 bits respectively (8 bits in
total). We use the lsb_reader to use LSB 0 bit numbering so we have
the following layout of the four fields inside the byte::

      7   6   5   4   3   2   1   0
    +-------+-----------+-------+---+
    | 0   1 | 0   1   1 | 1   0 | 0 |
    +-------+-----------+-------+---+
                                  ^
                                  |
       least significant +--------+
       bit

So the first field is at bit 0 which is the lest significant bit
inside the byte.

If on the other hand we use the msb_reader the example would be::

    auto reader = bitter::msb_reader<uint8_t, 1, 2, 3, 2>(0xdeadbeef);

We would have the following layout of the four fields inside the byte:

      0   1   2   3   4   5   6   7
    +---+-------+-----------+-------+
    | 0 | 1   0 | 1   1   1 | 0   0 |
    +---+-------+-----------+-------+
      ^
      |             most significant
      +-----------+ bit


License
=======
For more info on the license see the LICENSE file
