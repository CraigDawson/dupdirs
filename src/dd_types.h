// C/C++ File
// AUTHOR:   cxd1
// FILE:     dd_types.h
// ROLE:     Types for DupDir
// CREATED:  2014-08-25 22:13:39
// MODIFIED: 2014-09-08 17:35:11

#pragma once
#include "cxd_license.h"

#include <list>
#include <vector>
#include <string>
#include <utility>
#include <cstdint>

using string_list  = std::list<std::string>;
using str_int_pair = std::pair<std::string, int>;
using pair_list    = std::list<str_int_pair>;
using pair_vector  = std::vector<std::pair<std::string, uint32_t>>;

