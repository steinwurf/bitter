// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file
#include <bitter/bitfield_writer.hpp>

#include <vector>
#include <cstdint>

// 32 bit with
// TCP Header format source: http://www.freesoft.org/CIE/Course/Section4/8.htm
// 0                   1                   2                   3
// 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// |          Source Port          |       Destination Port        |
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// |                        Sequence Number                        |
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// |                    Acknowledgment Number                      |
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// |  Data |           |U|A|P|R|S|F|                               |
// | Offset| Reserved  |R|C|S|S|Y|I|            Window             |
// |       |           |G|K|H|T|N|N|                               |
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// |           Checksum            |         Urgent Pointer        |
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// |                    Options                    |    Padding    |
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// |                             data                              |
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class tcp_header_writer
{
public:
    using header_fields =
          bitter::bitfield_writer<
                                16, 16, 32, 32,
                                4, 6, 1, 1, 1,
                                1, 1, 1, 16,
                                16, 16, 24, 8>;
    enum class field
    {
        source_port = 0,
        destination_port = 1,
        sequence_number = 2,
        acknowledgment_number = 3,
        data_offset = 4,
        reserverd = 5,
        urg = 6,
        ack = 7,
        psh = 8,
        rst = 9,
        syn = 10,
        fin = 11,
        window = 12,
        checksum = 13,
        urgent_pointer = 14,
        options = 15,
        padding = 16
    };

public:
    tcp_header_writer(header_fields writer):
    m_writer(writer)
    {

    }

    tcp_header_writer(std::vector<uint8_t> data):
    m_writer(header_fields(data))
    {

    }

    void source_port(uint16_t value)
    {
        m_writer.write<(uint32_t) field::source_port>(value);
    }

    void destination_port(uint16_t value)
    {
        m_writer.write<(uint32_t) field::destination_port>(value);
    }

    void sequence_number(uint32_t value)
    {
        m_writer.write<(uint32_t) field::sequence_number>(value);
    }

    void acknowledgment_number(uint32_t value)
    {
        m_writer.write<(uint32_t) field::acknowledgment_number>(value);
    }

    // As the best fiting data type for a nibble is a byte
    // As it cannot fit in a bool
    void data_offset(uint8_t value)
    {
        m_writer.write<(uint32_t) field::data_offset>(value);
    }

    void reserverd(uint8_t value)
    {
        m_writer.write<(uint32_t) field::data_offset>(value);
    }

    void urg(bool value)
    {
        m_writer.write<(uint32_t) field::urg>(value);
    }

    void ack(bool value)
    {
        m_writer.write<(uint32_t) field::ack>(value);
    }
    void psh(bool value)
    {
        m_writer.write<(uint32_t) field::psh>(value);
    }
    void rst(bool value)
    {
        m_writer.write<(uint32_t) field::rst>(value);
    }
    void syn(bool value)
    {
        m_writer.write<(uint32_t) field::syn>(value);
    }
    void fin(bool value)
    {
        m_writer.write<(uint32_t) field::fin>(value);
    }

    void window(uint16_t value)
    {
        m_writer.write<(uint32_t) field::window>(value);
    }

    void checksum(uint16_t value)
    {
        m_writer.write<(uint32_t) field::checksum>(value);
    }

    void urgent_pointer(uint16_t value)
    {
        m_writer.write<(uint32_t) field::urgent_pointer>(value);
    }

    // As uint16_t, might not be enough to handle options, we set it to uint32_t
    // As the size of options is 24
    void options(uint32_t value)
    {
        m_writer.write<(uint32_t) field::options>(value);
    }

    void padding(uint8_t value)
    {
        m_writer.write<(uint32_t) field::padding>(value);
    }

    std::vector<uint8_t> data()
    {
        return m_writer.data();
    }

private:
    header_fields m_writer;
};
