#include <iostream>
#include "log.h"
#include "fts_wrapper.h"
#include "cxd_license.h"

using namespace std;

ostream& operator<<(ostream& os, const FileTraversalSystem& fts)
{
    return fts.ftsDump(os);
}
ostream& operator<<(ostream& os, const FileTraversalSystem* fts)
{
    return fts->ftsDump(os);
}



