void print_byte(uint8_t byte)
{
    for(int i = 0; i  < 8; ++i)
    {
        auto position = 7 - i;
        auto bit = (byte >> position) & 0x1;
        std::cout << static_cast<uint32_t>(bit);
    }
    std::cout << " ";
}
