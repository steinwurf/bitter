// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#include <cstdint>
#include <cassert>
#include <vector>

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
            return group_size_<Group, Groups...>();
        }

        template<int Group>
        uint64_t group_offset()
        {
            return offset_<Group, Groups...>();
        }


        template<int Group, typename Type>
        void write(Type data)
        {
            auto size = group_size<Group>();
            auto offset = group_offset<Group>();
            auto index = calculated_index(offset);
            if((offset + size) / 8 != 1)
            {
                if((offset + size) % 8 == 0)
                {
                    auto data_vector =
                         split_data_fitting_byte_size(data, offset, size);
                    write_data_vector(data_vector);
                }
                else
                {
                    auto bits = amount_of_bits_for_prior_byte(offset, size);
                    uint8_t prior_data = data >> (size - bits);
                    data = (data << bits) >> bits; // clear away the new bits
                    if((size - bits) % 8 == 0)
                    {
                        write_bits(prior_data, offset, index);
                        auto data_vector =
                             split_data_fitting_byte_size(
                                                          data,
                                                          offset + bits);
                        write_data_vector(data, offset + bits, index + 1);
                    }
                    else
                    {
                        auto trailing_bits =
                            amount_of_bits_for_prior_byte(offset
                                                          + bits,
                                                          size - bits);

                        // Clear away all data but trailing
                        uint8_t trailing_data = (data << (size - trailing_bits))
                                                 >> (size - trailing_bits);
                        uint64_t next_index = index;
                        // clear trailing data away
                        if(size - bits - trailing_bits == 16)
                        {
                            uint16_t remaing_data = data >> trailing;
                            write_data_vector(data, offset + bits, index + 1);
                            offset += 16;
                            next_index += 3;

                        }
                        else if(size - bits - trailing_bits == 32)
                        {
                            uint32_t remaing_data = data >> trailing;
                            write_data_vector(data, offset + bits, index + 1);
                            next_index += 5;
                            offset += 32;
                        }
                        else
                        {
                            uint64_t remaing_data = data >> trailing;
                            write_data_vector(data, offset + bits, index + 1);
                            offset += 64;
                            next_index += 9;
                        }
                        writer_bits(trailing, offset, next_index);
                    }
                }
            }
            else
            {
                writer_bits(data, offset, index);
            }
        }

        // // Written most significant bit first
        // template<int Group, typename InputType>
        // void write(InputType data)
        // {
        //     auto group_offset = offset<Group>();
        //     auto index = calculated_index(group_offset);
        //     auto size = group_size<Group>();
        //
        //     // Check if data fits in a byte
        //     if((group_offset + size) / 8 != 1)
        //     {
        //         if((group_offset + size) % 8  == 0)
        //         {
        //             auto data_vector =
        //             split_data_fitting_byte_size(data, group_offset, size);
        //             write_data_vector(data_vector, group_offset);
        //         }
        //         else
        //         {
        //             auto bits = amount_of_bits_for_prior_byte(group_offset, size);
        //             if((size - bits) % 8 == 0)
        //             {
        //                 uint8_t prior_data = data >> (size - bits);
        //                 write_bits(prior_data, group_offset, index);
        //                 if(size - bits == 16)
        //                 {
        //                     //uint16_t next_data = (data << bits) >> bits;
        //
        //                 }
        //             }
        //             else
        //             {
        //                 auto end_bits = amount_of_bits_for_prior_byte(group_offset, (size - bits));
        //
        //             }
        //         }
        //     }
        //     else
        //     {
        //         write_bits(data, group_offset, index);
        //     }
        // }

        uint8_t* data()
        {
            return m_data;
        }

            //     if(size / 16 == 1)
            //     {
            //
            //     }
            //     else if(size / 32 == 1)
            //     {
            //
            //     }
            //     else if(size / 64 == 1)
            //     {
            //
            //     }
            //     else
            //     {
            //         assert(size <= 64
            //             && "We do not support flags longer than 64 bit of length");
            //         }
            //
            //         auto bits = amount_of_bits_for_prior_byte(group_offset, size);
            //         uint8_t new_data = data >> (size - bits);
            //
            //
            //     }
            //     else
            //     {
            //         uint8_t shift = 7 - offset; // what if offset is large that 8
            //         m_data[index] = m_index |= data << shift; // Data must be uint8_t
            //     }
            // }

        private:

            // Write data most significant bit first
            void write_bits(uint8_t data, uint64_t offset, uint64_t index)
            {
                // give correct offset in current byte
                uint64_t shift = 7 - (offset - (index * 8));
                m_data[index] = m_data[index] |= data << shift;

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
                    return group_size_<Group, InputGroups...>();
                }
            }

            template<int Group, int NextGroup, int... InputGroups>
            uint64_t group_offset_()
            {
                if(sizeof...(Groups) - Group == sizeof...(InputGroups) + 1)
                {
                    return 0;
                }
                else
                {
                    return NextGroup + group_offset_<Group, InputGroups...>();
                }
            }

            template<int Group>
            uint64_t offset_()
            {
                return 0;
            }

            uint64_t calculated_index(uint64_t offset)
            {
                return offset / 8;
            }

            uint64_t amount_of_bits_for_prior_byte(uint64_t offset,
                                                   uint64_t size)
            {
                uint64_t temp = 0;
                while(((offset + size) - temp) / 8 != 1)
                {
                    temp++;
                }
                return temp;
            }

            template<typename Type>
            std::vector<uint8_t> split_data_fitting_byte_size(Type data, uint64_t size)
            {
                std::vector<uint8_t> data_vector;
                if(size == 16)
                {
                    data_vector.push_back(data >> 8);
                    data_vector.push_back((data << 8) >> 8);
                }
                else if(size == 32)
                {
                    data_vector.push_back(data >> 24);
                    data_vector.push_back((data << 8) >> 24);
                    data_vector.push_back((data << 16) >> 24);
                    data_vector.push_back((data << 24) >> 24);
                }
                else
                {
                    // Validate correctness
                    data_vector.push_back(data >> 56);
                    data_vector.push_back((data << 8) >> 56);
                    data_vector.push_back((data << 16) >> 56);
                    data_vector.push_back((data << 24) >> 56);
                    data_vector.push_back((data << 32) >> 56);
                    data_vector.push_back((data << 40) >> 56);
                    data_vector.push_back((data << 48) >> 56);
                }

                return data_vector;
            }

            void write_data_vector(std::vector<uint8_t> data_vector,
                                   uint64_t group_offset)
            {
                for(uint8_t entry : data_vector)
                {
                    auto index = calculated_index(group_offset);
                    write_bits(entry, 7, index);
                    group_offset += 8;
                }
            }


        private:
            uint8_t* m_data;
            uint64_t m_bits;
        };
    }
