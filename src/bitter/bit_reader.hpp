// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#include <cstdint>

namespace bitter
{
    class bit_reader
    {
    public:
        bit_reader(uint8_t data);
        uint8_t read(uint8_t offset, uint8_t size);

    private:
        uint8_t* m_data;
    };
}
