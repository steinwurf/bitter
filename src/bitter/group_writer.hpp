// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include <cstdint>
#include <cassert>

namespace bitter
{
template<Type FieldType, uint32_t Fields>
class field_writer
{
public:
    field_writer()
    {
        assert(sizeof(FieldType) * 8 == total_field_sizes());
        data.resize(sizeof(FieldType));
    }

    template<uint32_t Field, typename Type>
    void write_field(Type value)
    {
        auto size = field_size<Field>();
        auto offset = field_offset();
    }

private:

    uint32_t total_field_sizes()
    {
        return total_field_sizes_<Fieds...>();
    }

    template<uint32_t Field, uint32_t... InputFields>
    uint32_t total_field_sizes_()
    {
        return Field + total_field_sizes_<InputFields...>();
    }

    template<uint32_t Field>
    uint32_t total_field_sizes_()
    {
        return Field;
    }


    template<uint32_t Field>
    uint64_t field_size()
    {
        return field_size_<Field, Fields...>();
    }

    template<uint32_t Field, uint32_t NextField, uint32_t... InputFields>
    uint64_t field_size_()
    {
        if(sizeof...(Fields) - Field == sizeof...(InputFields) + 1)
        {
            return NextField;
        }
        else
        {
            return field_size_<Field, InputFields...>();
        }
    }

    template<uint32_t Field>
    uint64_t field_size_()
    {
        return 0;
    }

    Template<uint32_t Field>
    uint32_t field_offset()
    {
        field_offset<Field, Fields...>();
    }

    Template<uint32_t Field, uint32_t NextField, uint32_t... InputFields>
    uint32_t field_offset_()
    {
        if(sizeof...(Fields) - Field == sizeof(InputFields) + 1)
        {
            return 0;
        }
        else
        {
            return NextField + field_offset_<Field, InputFields...>();
        }
    }

    Template<uint32_t Field>
    uint32_t field_offset_()
    {
        return 0;
    }

private:
    FieldType data;

};
}
