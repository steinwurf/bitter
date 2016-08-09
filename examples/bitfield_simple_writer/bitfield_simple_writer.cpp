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

    std::vector<uint8_t> dummy(2);
    auto writer = bitter::bitfield_writer<1, 8>(dummy.data(), 9);
    //writer.write<1, bool>(true);
    //writer.write<2, uint8_t>(254);
    writer.write<1, uint8_t>(34U);
    writer.write<0, bool>(true);
    auto z = writer.data();

    std::cout << std::hex << static_cast<int>(z[0]) << std::endl;

    return 0;
}
