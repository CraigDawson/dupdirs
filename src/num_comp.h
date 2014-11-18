/* @file num_comp.h
 *
 * @brief Header for number compare functions
 *
 * @author Craig Dawson <Craig.Dawson@gmail.com>
 * @date 2014-11-18
 *
 */

#pragma once

#include "cxd_license.h"   // See for licensing information

extern pair_vector roots;

bool num_pair_comp(const str_int_pair& p1, const str_int_pair& p2);
bool num_str_comp(const std::string& s1, const std::string& s2);

