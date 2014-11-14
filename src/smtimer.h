/* @file smtimer.h
 *
 * @brief Small Timer Class for Debugging, etc. (C++11)
 *
 * @author Craig Dawson <Craig.Dawson@gmail.com>
 * @date 2014-07-20
 *
 */

#pragma once
#include "cxd_license.h"

#include <sstream>
#include <chrono>
#include <iomanip>
#include <locale>

/// FormatWithCommas from http://stackoverflow.com/questions/7276826/c-format-number-with-commas
template<class T>
std::string formatWithCommas(T value)
{
    std::stringstream ss;
    ss.imbue(std::locale(""));
    ss << std::fixed << value;
    return ss.str();
}

/// SMall Timer Class Namespace
namespace SMT
{
    using Clock = std::chrono::high_resolution_clock;
    using Us    = std::chrono::microseconds;

    using TimePoint = std::chrono::time_point<Clock>;
}

/// SMall Timer Class
class SmTimer
{
    public:
	SmTimer() {}
	~SmTimer() {}

	inline
	    void start() {
            start_ = SMT::Clock::now();
	    }

	inline
	    void stop() {
            stop_ = SMT::Clock::now();
	    }

	inline
	    long long timeUs() {
            return std::chrono::duration_cast<SMT::Us>(stop_ - start_).count();
	    }

	inline
        std::string timeUsStr(const std::string preface = "", bool unicode_mu = true) {
            std::stringstream ss;
            ss << preface
               << formatWithCommas(timeUs())
               << (unicode_mu ? "\u03BCs" : "us");
            return ss.str();
	    }

    private:
        SMT::TimePoint start_;
        SMT::TimePoint stop_;
};

