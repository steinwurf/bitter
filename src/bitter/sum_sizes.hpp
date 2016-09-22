// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include <cstdint>

namespace bitter
{
template<uint32_t Size0>
constexpr uint32_t sum_sizes()
{
    return Size0;
}

template<uint32_t Size0, uint32_t Size1, uint32_t... Sizes>
constexpr uint32_t sum_sizes()
{
    return Size0 + sum_sizes<Size1, Sizes...>();
}

}
