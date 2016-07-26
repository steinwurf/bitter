// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
namespace bitter
{

    template<unsigned ...> struct sum;
    template <unsigned size>
    sruct sum
    {
        enum { size = size };
    };
    template <unsigned size, unsigned... sizes>
    struct sum<size, sizes...>
    {
        enum { value - size + sum<sizes ...>::value };
    };
    static_assert(sum<1,2,3>::value == 6, "");

}
