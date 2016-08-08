#include <bitter/bitfield_writer.hpp>

#include <cstdint>
#include <vector>
#include <iostream>
#include <cstdint>

int main()
{
    // Set up stream for print and used for reset
    std::ios state(NULL);
    state.copyfmt(std::cout);

    std::vector<uint8_t> dummy(1);
    auto writer = bitter::bitfield_writer<8>(dummy.data(), 8);
    //writer.write<1, bool>(true);
    //writer.write<2, uint8_t>(254);
    writer.write<0, uint8_t>(64U);
    auto z = writer.data();

    std::cout << std::hex << static_cast<int>(z[0]) << std::endl;

    return 0;
}
