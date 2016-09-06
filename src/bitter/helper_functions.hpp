// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include <cstdint>

namespace bitter
{

    template<uint32_t Group, uint32_t NextGroup, uint32_t... RemainingGroups>
    uint32_t total_size_of_groups_()
    {
        return Group + total_size_of_groups_<NextGroup, RemainingGroups...>();
    }

    template<uint32_t Group>
    uint32_t total_size_of_groups_()
    {
        return Group;
    }
}
