// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include <type_traits>
#include <cstdint>

namespace bitter
{
template<typename DataType>
struct field
{
    field(DataType value): m_value(value)
    {

    }

    template<typename ReturnType>
    ReturnType read_as()
    {
        assert(sizeof(ReturnType) <= sizeof(DataType));

        if(std::is_same<bool, ReturnType>::value)
        {
            if(m_value == 0U)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        else
        {
            return (ReturnType) m_value;
        }
    }

    DataType m_value;
};
}
