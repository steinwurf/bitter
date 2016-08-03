#include <bitter/bitfields.hpp>

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



class tcp_header
{
    using header_fields =
          bitfields::bitfields<
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
    tcp_header(header_fields bitfield) :
    m_bitfield(bitfield)
    {

    }

    tcp_header(uint8_t* data, uint64_t size)
    {
        m_bitfield = header_fields(data);
        assert(m_bitfield.size() == size);
    }

    uint16_t source_port
    {
        return m_bitfield.get<uint16_t, field::source_port>();
    }

    uint16_t destination_port()
    {
        return m_bitfield.get<uint16_t, field::destination_port>();
    }

    uint32_t sequence_number()
    {
        return m_bitfield.get<uint32_t, field::sequence_number>();
    }

    uint32_t sequence_number()
    {
        return m_bitfield.get<uint32_t, field::sequence_number>();
    }

    uint32_t acknowledgment_number()
    {
        return m_bitfield.get<uint32_t, field::acknowledgment_number>();
    }

    // If a field does not fit neatly into a byte or multiple bytes use the
    // data type closest to the field size, but which is big enough to contain
    // it without losing precission.
    uint8_t data_offset()
    {
        // Bitter will figure out, the correct size of the field and not retrivew
        // more data than requested.
        return m_bitfield.get<uint8_t, field::data_offset>();
    }

    uint8_t reserverd()
    {
        return m_bitfield.get<uint8_t, field::reserverd>();
    }

    // Fields owhich have the size of a single bool, can be containeed
    // in a bool
    bool urg()
    {
        return m_bitfield.get<bool, field::urg>();
    }

    bool ack()
    {
        return m_bitfield.get<bool, field::ack>();
    }

    bool psh()
    {
        return m_bitfield.get<bool, field::psh>();
    }

    bool rst()
    {
        return m_bitfield.get<bool, field::rst>();
    }

    bool syn()
    {
        return m_bitfield.get<bool, field::syn>();
    }

    bool fin()
    {
        return m_bitfield.get<bool, field::fin>();
    }

    uint16_t window()
    {
        return m_bitfield.get<uint16_t, field::window>();
    }

    uint16_t checksum()
    {
        return m_bitfield.get<uint16_t, field::checksum>();
    }

    uint16_t urgent_pointer()
    {
        return m_bitfield.get<uint16_t, field::urgent_pointer>();
    }

    uint32_t options()
    {
        return m_bitfield.get<uint16_t, field::options>();
    }

    uint8_t padding()
    {
        return m_bitfield.get<uint8_t, field::padding>();
    }
private:
    header_fields m_bitfield;

};