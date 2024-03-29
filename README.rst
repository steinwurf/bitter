Bitter
======

|Linux make-specs| |Windows make-specs| |MacOS make-specs| |Linux CMake| |Windows CMake| |MacOS CMake| |Valgrind| |No Assertions| |Clang Format| |Cppcheck|

.. |Linux make-specs| image:: https://github.com/steinwurf/bitter/actions/workflows/linux_mkspecs.yml/badge.svg
   :target: https://github.com/steinwurf/bitter/actions/workflows/linux_mkspecs.yml
   
.. |Windows make-specs| image:: https://github.com/steinwurf/bitter/actions/workflows/windows_mkspecs.yml/badge.svg
   :target: https://github.com/steinwurf/bitter/actions/workflows/windows_mkspecs.yml

.. |MacOS make-specs| image:: https://github.com/steinwurf/bitter/actions/workflows/macos_mkspecs.yml/badge.svg
   :target: https://github.com/steinwurf/bitter/actions/workflows/macos_mkspecs.yml
   
.. |Linux CMake| image:: https://github.com/steinwurf/bitter/actions/workflows/linux_cmake.yml/badge.svg
   :target: https://github.com/steinwurf/bitter/actions/workflows/linux_cmake.yml

.. |Windows CMake| image:: https://github.com/steinwurf/bitter/actions/workflows/windows_cmake.yml/badge.svg
   :target: https://github.com/steinwurf/bitter/actions/workflows/windows_cmake.yml
   
.. |MacOS CMake| image:: https://github.com/steinwurf/bitter/actions/workflows/macos_cmake.yml/badge.svg
   :target: https://github.com/steinwurf/bitter/actions/workflows/macos_cmake.yml

.. |Clang Format| image:: https://github.com/steinwurf/bitter/actions/workflows/clang-format.yml/badge.svg
   :target: https://github.com/steinwurf/bitter/actions/workflows/clang-format.yml

.. |No Assertions| image:: https://github.com/steinwurf/bitter/actions/workflows/nodebug.yml/badge.svg
   :target: https://github.com/steinwurf/bitter/actions/workflows/nodebug.yml

.. |Valgrind| image:: https://github.com/steinwurf/bitter/actions/workflows/valgrind.yml/badge.svg
   :target: https://github.com/steinwurf/bitter/actions/workflows/valgrind.yml

.. |Cppcheck| image:: https://github.com/steinwurf/bitter/actions/workflows/cppcheck.yml/badge.svg
   :target: https://github.com/steinwurf/bitter/actions/workflows/cppcheck.yml

Is a lightweight header only C++ API, for reading and writing single bit
fields.

.. contents:: Table of Contents:
   :local:

bitter can be used to read or write individual bits or groups of bits
inside native data types.

Usage
-----

bitter provides 4 different readers/writers::

    bitter::lsb0_writer<Type, Fields...>();
    bitter::lsb0_reader<Type, Fields...>();
    bitter::msb0_writer<Type, Fields...>();
    bitter::msb0_reader<Type, Fields...>();

Where ``Type`` is a unsigned integer type e.g. ``uint8_t``, ``uint16_t``,
``uint32_t`` etc. (``uint8_t`` is short for unsigned 8 bit, these types
are defined in the ``<ctdint>`` header). ``Fields...`` is a variadic
template argument specifying the different bit fields. The curiously
looking ``lsb0`` and ``msb0`` specifies the "bit numbering" used. In some
rare cases you may want to read e.g. 24 bits or 40 bits for which no
standard integer types are defined, however also for those you can use
bitter see Section `Generic sized bit fields`_ further down.

To use bitter for reading/writing bit fields you need to first decide on
what bit numbering scheme to use - if you never heard about this concept
before you can jump to the "Bit numbering (bit endianness)" section further
down. Here's the quick TL;DR:

bitter can be configured to place bit fields either from *left to right*
called MSB 0 (Most Significant Bit 0) mode or *right to left* called LSB 0
(Least Significant Bit 0) mode.

Example::

                   auto writer = bitter::lsb0_writer<bitter::u8, 4, 4>();
                                          ^     ^         ^      ^  ^
                                          |     |         |      |  |
    LSB 0 mode (fields right-to-left) <---+     |         |      |  |
                                                |         |      |  |
      We will write bits into a value <---------+         |      |  |
                                                          |      |  |
           The data type of the value <-------------------+      |  |
                                                                 |  |
         Field at index 0 with size 4 <--------------------------+  |
                                                                    |
         Field at index 1 with size 4 <-----------------------------+

Since we use LSB 0 mode the field with index 0 will the the right half (
bit 0-3) of the byte and the field with index 1 will be the left half (
bit 4-7). In MSB 0 mode this would have been opposite.

Writing a bit field
-------------------

Lets say we want to write the four bytes of a 32 bit integer individually::

LSB 0 mode
..........

::

    // Using an uint32_t data type divided into 4 bit fields each 8 bits in
    // size. The sum of the bit fields must match the number of bits in the
    // data type.
    auto writer = bitter::lsb0_writer<uint32_t, 8, 8, 8, 8>();

    writer.field<0>(0x12); // Write bits 0-7
    writer.field<1>(0x34); // Write bits 8-15
    writer.field<2>(0x56); // Write bits 16-23
    writer.field<3>(0x78); // Write bits 24-31

    assert(writer.data() == 0x78563412);

Use ``#include <bitter/lsb0_writer.hpp>`` to use the
``bitter::lsb0_writer``.

MSB 0 mode
..........

::

    // Using an uint32_t data type divided into 4 bit fields each 8 bits in
    // size. The sum of the bit fields must match the number of bits in the
    // data type.
    auto writer = bitter::msb0_writer<uint32_t, 8, 8, 8, 8>();

    writer.field<0>(0x12); // Write bits 24-31
    writer.field<1>(0x34); // Write bits 16-23
    writer.field<2>(0x56); // Write bits 8-15
    writer.field<3>(0x78); // Write bits 0-7

    assert(writer.data() == 0x12345678);

Use ``#include <bitter/msb0_writer.hpp>`` to use the
``bitter::msb0_writer``.

Reading a bit field
-------------------

Given a value we can also read the individual bit fields.

LSB 0 mode
..........

::

    auto reader = bitter::lsb0_reader<uint32_t, 8, 8, 8, 8>(0x12345678);

    uint8_t value0 = reader.field<0>().as<uint8_t>(); // Read bits 0-7
    uint8_t value1 = reader.field<1>().as<uint8_t>(); // Read bits 8-15
    uint8_t value2 = reader.field<2>().as<uint8_t>(); // Read bits 16-23
    uint8_t value3 = reader.field<3>().as<uint8_t>(); // Read bits 24-31

    assert(value0 == 0x78);
    assert(value1 == 0x56);
    assert(value2 == 0x34);
    assert(value3 == 0x12);

Use ``#include <bitter/lsb0_reader.hpp>`` to use the
``bitter::lsb0_reader``.

MSB 0 mode
..........

::

    auto reader = bitter::msb0_reader<uint32_t, 8, 8, 8, 8>(0x12345678);

    uint8_t value0 = reader.field<0>().as<uint8_t>(); // Read bits 0-7
    uint8_t value1 = reader.field<1>().as<uint8_t>(); // Read bits 8-15
    uint8_t value2 = reader.field<2>().as<uint8_t>(); // Read bits 16-23
    uint8_t value3 = reader.field<3>().as<uint8_t>(); // Read bits 24-31

    assert(value0 == 0x12);
    assert(value1 == 0x34);
    assert(value2 == 0x56);
    assert(value3 == 0x78);

Use ``#include <bitter/lsb0_reader.hpp>`` to use the
``bitter::lsb0_reader``.


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

    auto reader = bitter::lsb0_reader<uint8_t, 1, 2, 3, 2>(0xdeadbeef);

We have four fields of size 1, 2, 3, 2 bits respectively (8 bits in
total). We use the ``lsb0_reader`` to use LSB 0 bit numbering so we have
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

If on the other hand we use the ``msb0_reader`` the example would be::

    auto reader = bitter::msb0_reader<uint8_t, 1, 2, 3, 2>(0xdeadbeef);

We would have the following layout of the four fields inside the byte::

      0   1   2   3   4   5   6   7
    +---+-------+-----------+-------+
    | 0 | 1   0 | 1   1   1 | 0   0 |
    +---+-------+-----------+-------+
      ^
      |             most significant
      +-----------+ bit


Generic sized bit fields
------------------------

In some cases you may want to read/write an odd number of bytes e.g. 5
corresponding to 40 bits from//to a value. In that case you can use
bitter's generic data types (defined in ``src/bitter/types.hpp``) such
as ``u8``, ``u16``, ``u24``, ``u32``, ``u40`` etc.

Small example::

    auto reader = bitter::msb0_reader<bitter::u24, 4, 12, 8>(0x123456U);

    uint8_t value0 = reader.field<0>().as<uint8_t>(); // Read bits 0-3
    uint16_t value1 = reader.field<1>().as<uint16_t>(); // Read bits 4-15
    uint8_t value2 = reader.field<2>().as<uint8_t>(); // Read bits 16-23

    assert(value0 == 0x1);
    assert(value1 == 0x234);
    assert(value2 == 0x56);


Byte endianness
---------------

While bitter allows us to conveniently pack bit-fields into a value. It
does not deal with writing those values to memory according to a specific
byte order (endianess):

https://en.wikipedia.org/wiki/Endianness

To do that you can use our ``endian`` library available here:

https://github.com/steinwurf/endian


Use as Dependency in CMake
--------------------------

To depend on this project when using the CMake build system, add the following
in your CMake build script::

   add_subdirectory("/path/to/bitter" bitter)
   target_link_libraries(<my_target> steinwurf::bitter)

Where ``<my_target>`` is replaced by your target.


License
=======

The bitter library is released under the BSD license see the LICENSE.rst
file
