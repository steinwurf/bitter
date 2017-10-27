// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include <cstdint>
#include <type_traits>

#include "types.hpp"

namespace bitter
{
namespace detail
{
/// Base case for BitterTypes (see types.hpp)
template<class BitterType>
struct to_type
{
    static_assert(BitterType::size > 0, "DataType must have size.");
    static_assert(std::is_unsigned<typename BitterType::type>::value ,
        "DataType must have a nested type which is unsigned. "
        "See types.hpp");

    using type = BitterType;
};

/// Special case for integer types
template<>
struct to_type<uint8_t>
{
    using type = u8;
};

template<>
struct to_type<uint16_t>
{
    using type = u16;
};

template<>
struct to_type<uint32_t>
{
    using type = u32;
};

template<>
struct to_type<uint64_t>
{
    using type = u64;
};
}

/// Helper function that converts a Type to a BitterType which is
/// defined in types.hpp
///
/// If the Type is a BitterType the function is just the identity
/// i.e.:
///
///     bitter::to_type<bitter::u8> == bitter::u8
///
/// However, for other integer types such as uint8_t we have:
///
///     bitter::to_type<uint8_t> == bitter::u8
///
template<class Type>
using to_type = typename detail::to_type<Type>::type;

}
