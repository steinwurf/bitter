// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include <cstdint>
#include "types.hpp"

namespace bitter
{
template<class NativeType>
struct to_type;

template<>
struct to_type<uint8_t>
{
    using value = u8;
};
template<>
struct to_type<uint16_t>
{
    using value = u16;
};
template<>
struct to_type<uint32_t>
{
    using value = u32;
};
template<>
struct to_type<uint64_t>
{
    using value = u64;
};
}