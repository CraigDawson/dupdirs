// C/C++ File
// AUTHOR:   cxd
// FILE:     dupdir.cpp
// ROLE:     code for DupDir class
// CREATED:  2014-08-04 15:38:30
// MODIFIED: 2014-10-16 18:08:58

#include "cxd_license.h"

#include <QApplication>
#include "mainwindow.h"
#include "dupdir.h"

#include <cstring>
#include <cerrno>

int32_t     Depth::depth  {0};
pair_vector roots;

const string DELIM {"|"}; // For Testing
//const string DELIM {"\003"};   // TODO: ETX char ??

//
// Original num_str_comp() idea from:
// http://stackoverflow.com/questions/4622516/sorting-stdstrings-with-numbers-in-them
// now with heavy modification.
//
bool num_pair_comp(const str_int_pair& p1, const str_int_pair& p2)
{
    return num_str_comp(p1.first, p2.first);
}

bool num_str_comp(const string& s1, const string& s2)
{
    if (s1.empty() || s2.empty()) return false;

    string::const_iterator it1 = s1.begin(), it2 = s2.begin();

    auto found = s1.find(roots[0].first);
    auto p1l = roots[0].first.length();
    if (found == string::npos)
    {
        found = s1.find(roots[1].first);
        p1l = roots[1].first.length();
        if (found == string::npos)
        {
            it1 = s1.begin(), it2 = s2.begin();
            return lexicographical_compare(it1, s1.end(), it2, s2.end());
        }
    }
    string p1 = s1.substr(found + p1l);

    found = s2.find(roots[0].first);
    auto p2l = roots[0].first.length();
    if (found == string::npos)
    {
        found = s2.find(roots[1].first);
        p2l = roots[1].first.length();
        if (found == string::npos)
        {
            it1 = s1.begin(), it2 = s2.begin();
            return lexicographical_compare(it1, s1.end(), it2, s2.end());
        }
    }
    string p2 = s2.substr(found + p2l);

    return lexicographical_compare(p1.begin(), p1.end(), p2.begin(), p2.end());
}

///
/// --- DupDir members ---
///


/// retuns empty string for root not in path
/// and root == path
string DupDir::pathLessRoot(const string& root,
                            const string& path)
{
    auto rootLen = root.length();
    string rtnPathLessRoot;

    auto found = path.find(root);
    if (found != string::npos)
    {
        rtnPathLessRoot = path.substr(found + rootLen);
    }
    else
    {
        // rtnPathLessRoot is empty (no root in path)
    }

    return rtnPathLessRoot;
}

void DupDir::getListOfDirs(const string& dirname)
{
    if (rootNum == -1)
        startTimer();  // time whole run

    display->status("PASS 1: " + dirname);

    ++rootNum;
    roots.push_back(make_pair(dirname, 0));
    FILE_LOG << "root dir: [" << rootNum << "]  " << dirname;

    getListOfDirsWalker(dirname);
}

void DupDir::buildHashList()
{
    pair_list::iterator   it;

    for (it = dirList.begin(); it != dirList.end(); ++it)
    {
        string dirSum;

        if (getSingleDirHash((*it).first, dirSum))
        {
            dirsHashList.push_back(make_pair(dirSum, (*it).second));
        }
        else
        {
            FILE_LOG << "No files in ["
            << (*it).second << "]  "
            << (*it).first;

            dirsHashList.push_back(make_pair(dirSum, (*it).second));

            ++emptyDirs;
        }
    }
}

inline
bool DupDir::getSingleDirHash(string& dirname, string& dirSum)
{
    display->status("PASS 2: " + dirname);

    return getDirHashWalker(dirname, dirSum);
}

pair<int, int> DupDir::compSums()
{
    dirsHashList.sort(num_pair_comp);

    //tmp debug
    //fstream fs;
    //fs.open ("/tmp/dirsHashList.txt"
    //           , std::fstream::in | std::fstream::out | std::fstream::app);
    //for (auto d: dirsHashList)
    //    fs << d.second << ":" << d.first << endl;

    return checkRepeats();
}

/// modified internet example (stackoverflow)
vector<string>
DupDir::split(const string& s, const string& delim, const bool keep_empty)
{
    vector<string> result;

    if (delim.empty())
    {
        result.push_back(s);
        return result;
    }

    string::const_iterator substart = s.begin(), subend;
    while (true)
    {
        subend = search(substart, s.end(), delim.begin(), delim.end());
        string temp(substart, subend);
        if (keep_empty || !temp.empty())
        {
            result.push_back(temp);
        }
        if (subend == s.end())
        {
            break;
        }
        substart = subend + delim.size();
    }

    return result;
}

pair<int, int> DupDir::checkRepeats()
{
    pair_list::iterator     it;
    vector<string>          lastV;
    int                     lastRoot    = -1;
    bool                    first       = true;
    int                     dirs        = 0;
    int                     dups        = 0;
    int                     dupsSR      = 0;
    int                     nonDups     = 0;
    int                     nonDupsPLR  = 0;
    bool                    dup         = false;

    // TODO: work for empty dir???????   lastV empty on first time through

    for (it = dirsHashList.begin(); it != dirsHashList.end(); ++it)
    {
        const vector<string> v = split((*it).first, DELIM);

        if (first)          // first time thru there are no valid last* values
        {
            first = false;

            ++dirs;

            lastV    = v;
            lastRoot = (*it).second;

            continue;
        }

        if (dup)
        {
            lastV    = v;
            lastRoot = (*it).second;
            ++dirs;

            dup = false;

            continue;
        }

        auto plrCur = pathLessRoot(
                roots[(*it).second].first,
                v[1]);
        auto plrLast = pathLessRoot(
                roots[lastRoot].first,
                lastV[1]);

        if ((lastV[0] == v[0])                 // hashes last and current match?
                && (lastRoot != (*it).second)) // not in the same root?
        {
            display->out(lastV[1], v[1]);

            dup = true;

            ++dups;
        }
        else if ((lastV[0] == v[0])
                && (lastRoot == (*it).second))  // dups in same root?
        {
            display->out2(lastV[1], v[1]);

            ++dupsSR;
        }
        else                                     // not dups (ignore these - no value)
        {
            if (plrLast == plrCur)
            {
                ++nonDupsPLR;
            }

            nonDups++;
        }

        lastV    = v;
        lastRoot = (*it).second;
        ++dirs;
    }

    FILE_LOG << dups
        << " duplicate pair of directories out of "
        << dirs
        << "/"
        << (dirs/2)
        << " directories/pairs";

    FILE_LOG << "Non-dups: " << nonDups
        << ", Non-DupsPLR: " << nonDupsPLR
        << ", Dups: " << dups
        << ", DupsSR: " << dupsSR
        << ", dirs: "  << dirs
        << ", empty dirs: " << emptyDirs;

    for (auto root : roots)
        FILE_LOG << "Directories in root: " << root.first << " " << root.second;

    stopTimer("Time for this run");
    return make_pair(dups, dirs);
}

bool DupDir::getListOfDirsStep(FTSENT* node)
{
    if (node->fts_errno != 0)
        FILE_LOG << "DupDir::getListOfDirsStep() Error: " << strerror(node->fts_errno)
            << "\n\t" << node->fts_path;

    if (node->fts_info & FTS_D)
    {
        dirList.push_back(make_pair(string(node->fts_path), rootNum));
        ++roots[rootNum].second;
    }

    QApplication::processEvents(); // update events, widgets

    return true;
}

void DupDir::getListOfDirsWalker(const string& p)
{
    std::function<bool(FTSENT*)> s = [=](FTSENT* node) -> bool
    {
        return this->getListOfDirsStep(node);
    };

    fts.setPathAndOpen(p);

    fts.walker(s);
}

bool DupDir::getDirHashStep(FTSENT* node)
{
    string filename = node->fts_name;

    if ( ((node->fts_info & FTS_F)
            || (node->fts_info & FTS_D))
            && (node->fts_level == 1) )
    {
        string entry;

#ifdef FASTER_LESS_ACCURATE_METHOD
        // TODO: retest this
        //FileStat fs(dirname + "/" + filename);
        stringstream ss;
        ss << node->fts_statp->st_size << DELIM << filename;
        entry = ss.str();

#else   // this method takes 2s vs 0.1s (on test set)
        // but gets rid of false positives
        try
        {
            hashwrapper *hw1 = new sha256wrapper();
            hw1->test();
            string sha256 = hw1->getHashFromFile(node->fts_path);
            entry = sha256 + DELIM + filename;
            delete hw1;
        }
        catch (hlException& e)
        {
            cerr << "hlerror: #"
                << int(e.error_number())
                << " " << e.error_message()
                << endl;
        }
#endif
        // for both
        entryList.push_back(entry);
        ++numFiles;
    }

    QApplication::processEvents(); // update events, widgets

    return true;
}

bool DupDir::getDirHashWalker(const string& p, string& dirSum)
{
    std::function<bool(FTSENT*)> s = [=](FTSENT* node) -> bool
    {
        return this->getDirHashStep(node);
    };

    fts.setPathAndOpen(p);

    numFiles = 0;
    entryList.erase(entryList.begin(), entryList.end());

    fts.walker(s);

    if (numFiles == 0)
    {
        dirSum = "0" + DELIM + p;
        return false;
    }

    // sort file list
    entryList.sort(num_str_comp);  // each entry: "fileSz fileName"

    // sum file list
    HashWrapper hw;
    string sha256 = hw.getHash(entryList);
    dirSum = sha256 + DELIM + p;

    return true;
}


