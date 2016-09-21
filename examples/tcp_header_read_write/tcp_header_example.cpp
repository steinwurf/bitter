// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file

#include "tcp_header_writer.hpp"
#include "tcp_header_reader.hpp"

#include <iostream>

void print_byte(uint8_t byte)
{
    for (int i = 0; i  < 8; ++i)
    {
        auto position = 7 - i;
        auto bit = (byte >> position) & 0x1;
        std::cout << static_cast<uint32_t>(bit);
    }
    std::cout << " ";
}

int main()
{
    std::vector<uint8_t> data_vector;
    data_vector.resize(24);

    std::cout << "We are filling the writer with data: " << std::endl;
    auto writer = tcp_header_writer(data_vector);
    writer.source_port(128);
    writer.destination_port(255);
    writer.sequence_number(4096);
    writer.acknowledgment_number(2048);
    writer.data_offset(4);
    writer.reserverd();
    writer.urg(1);
    writer.ack(0);
    writer.psh(1);
    writer.rst(1);
    writer.syn(1);
    writer.fin(0);
    writer.window(96);
    writer.checksum(85);
    writer.urgent_pointer(87);
    writer.options(209);
    writer.padding(128);

    for (auto entry : writer.data())
    {
        print_byte(entry);
    }

    std::cout << "" << std::endl;
    std::cout << "We read the data written in the writer" << std::endl;
    auto reader = tcp_header_reader(writer.data());
    auto src_port = reader.source_port();
    std::cout << "Source port: " << static_cast<int>(src_port) << std::endl;
    auto dest_port = reader.destination_port();
    std::cout << "Destination port: " << static_cast<int>(dest_port) << std::endl;
    auto seq_number = reader.sequence_number();
    std::cout << "Sequence Number: " << static_cast<int>(seq_number) << std::endl;
    auto ack_number = reader.acknowledgment_number();
    std::cout << "Acknowledgment Number: " << static_cast<int>(ack_number)
              << std::endl;
    auto data_offset = reader.data_offset();
    std::cout << "Data offset: " << static_cast<int>(data_offset) << std::endl;
    auto reserverd = reader.reserverd();
    std::cout << "Reserved: " << static_cast<int>(reserverd) << std::endl;
    auto urg = reader.urg();
    std::cout << "Urg: " << urg << std::endl;

    return 0;
}
