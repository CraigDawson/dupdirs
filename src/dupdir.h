// C/C++ File
// AUTHOR:   cxd
// FILE:     dupdir.h
// CREATED:  2014-07-07 14:14:30
// MODIFIED: 2014-07-07 14:26:48

#pragma once

#include "cxd_license.h"   // See for licensing information

#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <iterator>
#include <algorithm>
#include <dirent.h>
#include <functional>
#include <utility>
#include <cstdlib>
#include <chrono>
#include <ctime>

#include <sys/stat.h>
#include <sys/types.h>

#include <hashlibpp.h>

#include "log.h"
#include <smtimer.h>
#include "dd_types.h"
#include "fts_wrapper.h"

extern pair_vector roots;

bool num_pair_comp(const str_int_pair& p1, const str_int_pair& p2);
bool num_str_comp(const string& s1, const string& s2);

/// Depth class is used to determine depth of roots
class Depth
{
    public:
        Depth() { ++depth; }

        ~Depth() { --depth; }

        int32_t getDepth() const {
            int32_t d = depth - 1;
            return (d < 0) ? 0 : d;
        }

    private:
        static int32_t depth;
};

/// Encapsulate finding file size
class FileStat
{
    public:
        FileStat() {}
        ~FileStat() {}

        FileStat(const string& file) { stat(file.c_str(), &info); }

        int size() { return info.st_size; }

    protected:
        struct stat info;
};

/// Encapsulate means of calculating hash sum
class HashWrapper
{
    public:
        HashWrapper()
        {
            hw = new sha256wrapper();
        }
        ~HashWrapper()
        {
            delete hw;
        }
        string getHash(const string_list& sl)
        {
            return hw->getHashFromListOfStrings(sl);
        }
    private:
        hashwrapper* hw;
};

///
/// DupDir is the main class that does all the work
///
class DupDir
{
public:
    /// public member functions ---
    DupDir(MainWindow* display) : display{display} {}

    ~DupDir() { roots.erase(roots.begin(), roots.end()); }

    void getListOfDirs(const string& dirname);  // TODO:Add 2nd arg to count dirs in each root??

    void buildHashList();

    pair<int, int> compSums();

private:
    /// private member variables ---
    pair_list       dirList;
    pair_list       dirsHashList;
    int             rootNum {-1}; // will pre-increment to 0
    int32_t         emptyDirs {0};
    MainWindow*     display;

    string_list     entryList;
    int             numFiles {0};

    Depth d;

    /// private member functions ---
    string pathLessRoot(const string& root, const string& path);

    bool getSingleDirHash(string& dirname, string& dirSum);

    vector<string>
    split(const string& s,
          const string& delim,
          const bool keep_empty = true);

    pair<int, int> checkRepeats();

    FileTraversalSystem fts;

    /// FTS support functions (see fts_wrapper.h) ---
    bool getListOfDirsStep(FTSENT* node);
    void getListOfDirsWalker(const string& p);

    bool getDirHashStep(FTSENT* node);
    bool getDirHashWalker(const string& p, string& dirSum);

    /// Timer & supporting functions ---
    SmTimer st;

    inline
    void startTimer()
    {
        st.start();
    }

    inline
    void stopTimer(const string& str)
    {
        st.stop();
        string so { st.timeUsStr(str + ": ") };
        FILE_LOG << so;
        display->outLine(so);
    }
    /// EOTimer & supporting functions ---
};

