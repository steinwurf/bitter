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

    template<int Group>
    uint64_t group_size()
    {
        return group_size_<Group, Groups>()
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

    template<int Group, int NextGroup, int... InputGroups>
    uint64_t group_size_()
    {
        if((sizeof...(Groups) - Group) == sizeof...(InputGroups)  + 1)
        {
            return NextGroup;
        }
        else
        {
            returng group_size_<Group, InputGroups...>();
        }
    }
private:
    uint8_t* m_data;
    uint64_t m_bits;
};
}
