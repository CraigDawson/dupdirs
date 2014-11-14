/* @file fts_wrapper.cpp
 *
 * @brief FTS wrapper class
 *
 * @author Craig Dawson <Craig.Dawson@gmail.com>
 * @date 2014-11-14
 *
 */

#include "cxd_license.h"

#include <iostream>
#include "log.h"
#include "fts_wrapper.h"

using namespace std;

ostream& operator<<(ostream& os, const FileTraversalSystem& fts)
{
    return fts.ftsDump(os);
}
ostream& operator<<(ostream& os, const FileTraversalSystem* fts)
{
    return fts->ftsDump(os);
}



