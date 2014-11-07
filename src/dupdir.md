# class DupDir
### cxd 8/15/14

## Definitions
using string_list = list<string>;
using pair_vector = vector< pair<long, string> >;

bool num_str_comp(const string& s1, const string& s2);

## Variables
* string_list  dirList;
* string_list  dirsHashList;
* pair_vector  roots;
* MainWindow*  display;
* const string DELIM  // ETX char
* Depth        d;

## Functions
* void getListOfDirs(const string& dirname);  // Add directories to dirList

* void buildHashList(); // For each dir get hash and add to dirsHashList
    * bool getSingleDirHash(string& dirname, string& dirSum); // make entry for each file in dir: "fs + DELIM + filename"
        * entryList.sort(num_str_comp); // sort entry list
        * string getHash(string_list sl) // get hash and return dirSum: "hash + DELIM + dirname"

* pair<int, int> compSums() // sort dir hash list and return pair<dups, dirs> 
    * dirsHashList.sort(num_str_comp); // sort directory hash list
    * pair<int, int> checkRepeats(); // go through list looking for duplicates
        * vector<string> split(const string& s, const string& delim, const bool keep_empty = true);
