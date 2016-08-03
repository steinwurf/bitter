#include <vector>
#include <iostream>
#include <cstdint>
#include <bitset>

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
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;
    auto group_zero = bf.get<uint8_t, 0>();
    std::cout << "Size of group zero: " << sizeof(group_zero);
    std::cout << " content of group zero " << group_zero << std::endl;
    std::cout << "offset of group zero: " << bf.offset<0>() << std::endl;
    std::bitset<8> a(group_zero);
    std::cout << "Binary representation of Group zero: " << a << std::endl;
    std::cout << "We try to hex " << std::hex << static_cast<int>(group_zero) << std::endl;
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;
    auto group_one = bf.get<uint16_t, 1>();
    std::cout << "Size of group one: " << sizeof(group_one);
    std::cout << " content of group one " << group_one << std::endl;
    std::cout << "offset of group one: " << bf.offset<1>() << std::endl;
    std::bitset<16> b(group_one);
    std::cout << "Binary representation of Group one: " << b<< std::endl;
    std::cout << "We try to hex " << std::hex << static_cast<int>(group_one) << std::endl;
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;
    auto group_two = bf.get<uint32_t, 2>();
    std::cout << "Size of group two: " << sizeof(group_two);
    std::cout << " content of group two " << group_two << std::endl;
    std::cout << "offset of group two: " << bf.offset<2>() << std::endl;
    std::bitset<32> c(group_two);
    std::cout << "Binary representation of Group two: " << c << std::endl;
    std::cout << "We try to hex " << std::hex << static_cast<int>(group_two) << std::endl;
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;
    auto group_three = bf.get<uint64_t, 3>();
    std::cout << "Size of group three: " << sizeof(group_three);
    std::cout << " content of group three " << group_three << std::endl;
    std::cout << "offset of group three: " << bf.offset<3>() << std::endl;
    std::bitset<64> d(group_three);
    std::cout << "Binary representation of Group three: " << d << std::endl;
    std::cout << "We try to hex " << std::hex << static_cast<int>(group_three) << std::endl;
}
