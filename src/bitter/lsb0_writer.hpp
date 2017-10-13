// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include "writer.hpp"

namespace bitter
{
/// @breif Reader class used for reading the content
///        of the value parsed to the reader at initialisation
template<typename DataType, uint32_t... Sizes>
using lsb0_writer = writer<DataType, lsb0, Sizes...>;
}
