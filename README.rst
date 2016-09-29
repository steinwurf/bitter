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

License
=======
For more info on the license see the LICENSE file
