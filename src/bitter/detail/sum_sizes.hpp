// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include <cstdint>

namespace bitter
{
/// @brief Template based functions for getting the total size of the
///        variadic template Sizes.
template<std::size_t Size0>
constexpr std::size_t sum_sizes()
{
    return Size0;
}

template<std::size_t Size0, std::size_t Size1, std::size_t... Sizes>
constexpr std::size_t sum_sizes()
{
    return Size0 + sum_sizes<Size1, Sizes...>();
}

}
