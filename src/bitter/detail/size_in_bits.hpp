// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include <cstddef>
#include <cstdint>

namespace bitter
{
/// @brief function for getting the size of DataType in bits
template<class DataType>
constexpr std::size_t size_in_bits()
{
    return DataType::size * 8U;
}

template<>
constexpr std::size_t size_in_bits<bool>()
{
    return 1U;
}

template<>
constexpr std::size_t size_in_bits<uint8_t>()
{
    return sizeof(uint8_t) * 8U;
}

template<>
constexpr std::size_t size_in_bits<uint16_t>()
{
    return sizeof(uint16_t) * 8U;
}

template<>
constexpr std::size_t size_in_bits<uint32_t>()
{
    return sizeof(uint32_t) * 8U;
}

template<>
constexpr std::size_t size_in_bits<uint64_t>()
{
    return sizeof(uint64_t) * 8U;
}
}
