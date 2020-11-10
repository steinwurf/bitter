// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.
#pragma once

#include <cstddef>
#include "reader.hpp"

namespace bitter
{
/// @brief Reader class used for reading the content
///        of the value parsed to the reader at initialization
template<typename DataType, std::size_t... Sizes>
using lsb0_reader = reader<DataType, lsb0, Sizes...>;
}
