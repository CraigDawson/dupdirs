/* @file fts_wrapper.h
 *
 * @brief Wrapper class for FTS (partial)
 *
 * @author Craig Dawson <Craig.Dawson@gmail.com>
 * @date 2014-09-22
 *
 */

#pragma once
#include "cxd_license.h"

#include "log.h"
#include "quote_iomanip.h"
#include <fts.h>
#include <functional>
#include <ostream>
#include <system_error>
#include <cstring>

class FileTraversalSystem
{
    public:
        FileTraversalSystem(const std::string path,
                            int options = FTS_COMFOLLOW | FTS_LOGICAL | FTS_NOCHDIR,
                            int (*compar)(const FTSENT **, const FTSENT **) = 0)
        {
            setPathAndOpen(path, options, compar);
        }

        FileTraversalSystem()
        {
            ppath = nullptr;
        }

        ~FileTraversalSystem()
        {
            if (ppath != nullptr)
            {
                delete ppath;
                if (fts_close(tree) != 0)
                    throw std::system_error(errno, std::system_category());
            }
        }

        void setPathAndOpen(const std::string& path,
                            int options = FTS_COMFOLLOW | FTS_LOGICAL | FTS_NOCHDIR,
                            int (*compar)(const FTSENT **, const FTSENT **) = 0)
        {
            // If 'options' is not or'ed with FTS_NOCHDIR,
            // fts may change the program's current working directory.
            // See FTS man page.
            ppath = new char[path.size() + 1];
            strncpy(ppath, path.c_str(), path.size() + 1);
            char* const paths[] = {ppath, 0};
            tree = fts_open(paths, options, compar);
            if (!tree) throw std::system_error(errno, std::system_category());
        }

        FTSENT* read() const { return fts_read(tree); }

        void walker(std::function<bool(FTSENT*)> step)
        {
            if (ppath == nullptr)
                throw std::string("FTS::walker(): ppath not set thru constructor or setPathAndOpen member");

            // Initialize ftsp with as many argv[] parts as possible.
            FTSENT* chp = fts_children(tree, 0);
            if (chp == NULL)
            {
                FILE_LOG << "FTS::walker(): no files to traverse";

                return;               // no files to traverse
            }
#ifdef DEBUG
            ftsPrint();
#endif
            while (FTSENT* node = read())
            {
                if (node->fts_level > 0 && node->fts_name[0] == '.')
                    fts_set(tree, node, FTS_SKIP);
                else
                    if (!step(node)) break;
            }

            if (errno)
                throw std::system_error(errno, std::system_category());
        }

        FTS* getTree() { return tree; }

        std::ostream& ftsDump(std::ostream& out) const
        {
            FTSENT* ent  = fts_children(tree, 0);
            out << "fts_info =\t"     << ent->fts_info << "\n"
                << "fts_accpath =\t"  << ent->fts_accpath << "\n"
                << "fts_path =\t"     << ent->fts_path << "\n"
                << "fts_pathlen =\t"  << ent->fts_pathlen << "\n"
                << "fts_name =\t"     << ent->fts_name << "\n"
                << "fts_namelen =\t"  << ent->fts_namelen << "\n"
                << "fts_level =\t"    << ent->fts_level << "\n"
                << "fts_errno =\t"    << ent->fts_errno << "\n"
                << "fts_number =\t"   << ent->fts_number << std::endl;

            return out;
        }

        void ftsPrint() const
        {
            FTSENT* ent  = fts_children(tree, 0);

            FILE_LOG << "fts_info =\t"     << ent->fts_info << "\n"
                << "fts_accpath =\t"  << Quote('"') << ent->fts_accpath << "\n"
                << "fts_path =\t"     << Quote('"') << ent->fts_path << "\n"
                << "fts_pathlen =\t"  << ent->fts_pathlen << "\n"
                << "fts_name =\t"     << Quote('"') << ent->fts_name << "\n"
                << "fts_namelen =\t"  << ent->fts_namelen << "\n"
                << "fts_level =\t"    << ent->fts_level << "\n"
                << "fts_errno =\t"    << ent->fts_errno << "\n"
                << "fts_number =\t"   << ent->fts_number << std::endl;
       }

    private:
        FTS*    tree;
        char*   ppath {nullptr};
};


