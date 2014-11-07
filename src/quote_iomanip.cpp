#include "quote_iomanip.h"

// When you pass an object of type Quote to an ostream it returns
// an object of Quote::Quoter that has overloaded the << operator for
// all types. This will quote the next object and the return the stream
// to continue processing as normal.
Quote::Quoter operator<<(std::ostream& str,Quote const& quote)
{
    return Quote::Quoter(quote,str);
}



