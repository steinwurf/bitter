======
Bitter
======

Is a lightweight Header only C++ API, for reading and writing single bit and
varying length byte fields.

Writing a bit field
-------------------

Lets say we want to write the four bytes of a 32 bit integer individually::

    // Write into a 16 bit data type divided into 3 bit fields of size 1, 2, and
    // 13 bits respectively. The sum of sizes of the bit fields must match the
    // number of bits in the choosen data type.
    auto writer = bitter::writer<uint16_t, 1, 2, 13>();

    writer.field<0>(1); // Write bit 0
    writer.field<1>(1); // Write bits 1-2
    writer.field<2>(1); // Write bits 3-15

    assert(writer.data() == 0b0000000000001011);

Use `#include <bitter/writer.hpp>` to use the `bitter::writer`.

Reading a bit field
-------------------

Given a value we can also read the individual bit fields. Based on the example
above lets read back the four bit fields from the uint32_t value.

    // Read from a 16 bit data type divided into 3 bit fields of size 1, 2, and
    // 13 bits respectively.
    auto reader = bitter::reader<uint16_t, 1, 2, 13>(0b0000000000001011);

    bool value0 = reader.field<0>().read_as<bool>(); // Read bit 0
    uint8_t value1 = reader.field<1>().read_as<uint8_t>(); // Read bits 1-2
    uint16_t value2 = reader.field<2>().read_as<uint16_t>(); // Read bits 3-15

    assert(value0 == 1);
    assert(value1 == 1);
    assert(value2 == 1);

Use `#include <bitter/reader.hpp>` to use the `bitter::reader`.

License
=======
For more info on the license see the LICENSE file
