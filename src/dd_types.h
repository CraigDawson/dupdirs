/* @file dd_types.h
 *
 * @brief Types for DupDir
 *
 * @author Craig Dawson <Craig.Dawson@gmail.com>
 * @date 2014-08-25
 *
 */

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

