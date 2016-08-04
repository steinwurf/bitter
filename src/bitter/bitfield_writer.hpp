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

        template<int Group>
        uint64_t offset()
        {
            return offset_<Group, Groups...>();
        }

        // Written most significant bit first
        template<int Group, typename InputType>
        void write<Group>(InputType data)
        {
            auto group_offset = offset<Group>();
            auto index = calculated_index(offset);
            auto size = group_size<Group>();

            // Check if data fits in a byte
            if((group_offset + size) / 8 != 1)
            {
                if((group_offset + size) % 8  == 0)
                {
                    auto data_vector =
                    split_data_fitting_byte_size(data, group_offset, size);

                    for(uint8_t entry : data_vector)
                    {
                        auto index = calculated_index(group_offset);
                        write_bits(entry, 7, index);
                        group_offset += 8;
                    }
                }
                else
                {
                    
                }
            }
            else
            {
                write_bits(data, offset, index)
            }
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
                m_data[index] = m_index |= data << shift;

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

            template<Group, int NextGroup, int... InputGroups>
            uint64_t offset_()
            {
                if(sizeof...(Groups) - Group == sizeof...(InputGroups) + 1)
                {
                    return 0;
                }
                else
                {
                    return NextGroup + offset_<Group, InputGroups...>();
                }
            }

            template<Group>
            uint64_t offset_()
            {
                return 0;
            }

            uint64_t calculated_index(uint64_t offset)
            {
                return offset / 8;
            }

            uint64_t amount_of_bits_for_prior_byte(uint64_t offset, uint64_t size)
            {
                uint64_t temp = 0
                while(((group_offset + size) - temp) / 8 != 1)
                {
                    temp++;
                }
            }

            template<typename Type>
            void split_data_for_writing(Type data, uint64_t size, uint64_t offset)
            {
                if((offset + size))
                {

                }
            }

            template<typename Type>
            std::vector<uint8_t> v; split_data_fitting_byte_size(Type data, uint64_t offset, uint64_t size)
            {
                std::std::vector<uint8_t> data_vector;
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

            template<typename Type, typename ComparedType>
            bool is_same_type()
            {
                return Type == ComparedType;
            }



        private:
            uint8_t* m_data;
            uint64_t m_bits;
        };
    }
