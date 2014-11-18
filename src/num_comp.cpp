/* @file num_comp.cpp
 *
 * @brief Number Compare Routines for Sorting
 *
 * @author Craig Dawson <Craig.Dawson@gmail.com>
 * @date 2014-11-18
 *
 */

#include <string>
#include "dd_types.h"
#include "num_comp.h"

//
// Original num_str_comp() idea from:
// http://stackoverflow.com/questions/4622516/sorting-stdstrings-with-numbers-in-them
// now with heavy modification.
//
bool num_pair_comp(const str_int_pair& p1, const str_int_pair& p2)
{
    return num_str_comp(p1.first, p2.first);
}

bool num_str_comp(const std::string& s1, const std::string& s2)
{
    if (s1.empty() || s2.empty()) return false;

    std::string::const_iterator it1 = s1.begin(), it2 = s2.begin();

    auto found = s1.find(roots[0].first);
    auto p1l = roots[0].first.length();
    if (found == std::string::npos)
    {
        found = s1.find(roots[1].first);
        p1l = roots[1].first.length();
        if (found == std::string::npos)
        {
            it1 = s1.begin(), it2 = s2.begin();
            return lexicographical_compare(it1, s1.end(), it2, s2.end());
        }
    }
    std::string p1 = s1.substr(found + p1l);

    found = s2.find(roots[0].first);
    auto p2l = roots[0].first.length();
    if (found == std::string::npos)
    {
        found = s2.find(roots[1].first);
        p2l = roots[1].first.length();
        if (found == std::string::npos)
        {
            it1 = s1.begin(), it2 = s2.begin();
            return lexicographical_compare(it1, s1.end(), it2, s2.end());
        }
    }
    std::string p2 = s2.substr(found + p2l);

    return lexicographical_compare(p1.begin(), p1.end(), p2.begin(), p2.end());
}


