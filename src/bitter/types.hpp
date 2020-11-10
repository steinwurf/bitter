// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include <cstdint>

namespace bitter
{
struct u8
{
    using type = uint8_t;
    static constexpr std::size_t size = 1;
};
struct u16
{
    using type = uint16_t;
    static constexpr std::size_t size = 2;
};
struct u24
{
    using type = uint32_t;
    static constexpr std::size_t size = 3;
};
struct u32
{
    using type = uint32_t;
    static constexpr std::size_t size = 4;
};
struct u40
{
    using type = uint64_t;
    static constexpr std::size_t size = 5;
};
struct u48
{
    using type = uint64_t;
    static constexpr std::size_t size = 6;
};
struct u56
{
    using type = uint64_t;
    static constexpr std::size_t size = 7;
};
struct u64
{
    using type = uint64_t;
    static constexpr std::size_t size = 8;
};
}
