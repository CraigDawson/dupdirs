/* @file quote_iomanip.h
 *
 * @brief Quote iomanip
 *
 * From http://stackoverflow.com/questions/535444/custom-manipulator-for-c-iostream
 * Note: There is a quoted() iomanip in C++14
 *
 * @author Craig Dawson <Craig.Dawson@gmail.com>
 * @date 2014-11-14
 *
 */

#pragma once
#include <iostream>
#include <iomanip>
#include <string>

// The Object that we put on the stream.
// Pass in the character we want to 'quote' the next object with.
class Quote
{
    public:
        Quote(char x)
            :m_q(x)
        {}
    private:
        // Classes that actual does the work.
        class Quoter
        {
            public:
                Quoter(Quote const& quote,std::ostream& output)
                    :m_q(quote.m_q)
                    ,m_s(output)
                {}

                // The << operator for all types. Outputs the next object
                // to the stored stream then returns the stream. 
                template<typename T>
                std::ostream& operator<<(T const& quoted)
                {
                    return m_s << m_q << quoted << m_q;
                }

            private:
                char            m_q;
                std::ostream&   m_s;
        };
        friend Quote::Quoter operator<<(std::ostream& str,Quote const& quote);

    private:
        char    m_q;
};
