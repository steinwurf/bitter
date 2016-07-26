// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <cstdint>

namespace store
{
    template<unsigned bits> struct store;
    template<> struct store<8> {typedef uint8_t type;};
    template<> struct store<16> {typedef uint8_t type;};
    template<> struct store<32> {typedef uint8_t type;};
    template<> struct store<64> {typedef uint8_t type;};
}
