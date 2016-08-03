#include <vector>
#include <iostream>
#include <cstdint>

#include <bitter/bitfields.hpp>

int main()
{
    std::vector<uint8_t> data
    {
        0x00, //0000 0000
        0xFF, //1111 1111
        0xF0, //1111 0000
        0x0F, //0000 1111
        0xA5, //1010 0101
        0x00, //0000 0000
        0xFF, //1111 1111
        0xF0, //1111 0000
        0x0F, //0000 1111
        0xA5, //1010 0101
        0x00, //0000 0000
        0xFF, //1111 1111
        0xF0, //1111 0000
        0x0F, //0000 1111
        0xA5, //1010 0101
        0x00, //0000 0000
        0xFF, //1111 1111
        0xF0, //1111 0000
        0x0F, //0000 1111
        0xA5, //1010 0101
    };

    auto bf = bitter::bitfields<8,16,32,64>(data.data(), data.size() * 8);
    auto size = bf.group_size<0>();
    std::cout << "Group 0 size: " << size << std::endl;
    size = bf.group_size<1>();
    std::cout << "Group 1 size: " << size << std::endl;
    size = bf.group_size<2>();
    std::cout << "Group 2 size: " << size << std::endl;
    size = bf.group_size<3>();
    std::cout << "Group 3 size: " << size << std::endl;

    auto group_zero = bf.get<uint8_t, 0>();
    std::cout << "Size of group zero: " << sizeof(group_zero);
    std::cout << " content of group zero " << group_zero << std::endl;

    auto group_one = bf.get<uint16_t, 1>();
    std::cout << "Size of group one: " << sizeof(group_one);
    std::cout << " content of group one " << group_one << std::endl;

    auto group_two = bf.get<uint32_t, 2>();
    std::cout << "Size of group two: " << sizeof(group_two);
    std::cout << " content of group two " << group_two << std::endl;

    auto group_three = bf.get<uint64_t, 3>();
    std::cout << "Size of group three: " << sizeof(group_three);
    std::cout << " content of group three " << group_three << std::endl;


}
