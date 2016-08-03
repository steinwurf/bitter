// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#include <cstdint>
#include <cassert>

namespace bitter
{
template<int... Groups>
class bitfield_writer
{
public:
    bitfield_writer(uint8_t* data, uint64_t bits):
    m_data(data),
    m_bits(bits)
    {

    }

    template<int Group, typename InputType>
    void write<Group>(InputType data)
    {

    }

private:

    template<InputType>
    void write_bit(InputType data, uint64_t offset)
    {
        assert(offset < m_bits);
    }

private:
    uint8_t* m_data;
    uint64_t m_bits;
};
}
