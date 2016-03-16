#include <string>
#include <boost/filesystem.hpp>

#include "filesystem.hpp"

using boost::filesystem::path;
using boost::filesystem::directory_entry;

namespace
{
    void copy_path(const path&, const path&, const path&);
    std::pair<path, path> split(const path&, const path&);
    void copy_directories(const path&, const path&, const path&);
    
    
    /**
     * @brief Splits a path given an ancestor.
     * @param par The ancestor path
     * @param sub The path to split
     * @return sub as split at par.
     * 
     * Example:
     * 
     * par = /home/username
     * sub = /home/username/stuff/myfile.txt
     * 
     * Return value:
     * std::pair<path, path>{"/home/username", "stuff/myfile.txt"}
     */
    inline std::pair<path, path> split(const path& par, const path& sub)
    {
        std::pair<path, path> s;
        s.first = par;
        path::iterator it(sub.begin()), it2(par.begin());
        
        for(;((it != sub.end()) && (it2 != par.end()) && (*it == *it2)); ++it, ++it2);
        for(; it != sub.end(); ++it)
        {
            s.second /= *it;
        }
        return s;
    }
    
    /**
     * @brief Copies a folder.
     * @param from_root The root folder that stuff is being copied from.
     * @param from the actual folder to copy.
     * @param to the destination folder
     */
    inline void copy_directories(const path& from_root, const path& from, const path& to)
    {
        using boost::filesystem::copy_directory;
        using boost::filesystem::is_directory;
        
        if(from == from_root)
        {
            if(!is_directory(to / from.filename())) copy_directory(from, (to / from.filename()));
        }
        
        path from_split(split(from_root, from).second), newto(to / from_root.filename()), newfrom(from_root);
        
        for(path::iterator it(from_split.begin()); it != from_split.end(); ++it)
        {
            newto /= *it;
            newfrom /= *it;
            if(!is_directory(newto))
            {
                copy_directory(newfrom, newto);
            }
        }
    }
    
    /**
     * @brief Copies a single file or folder into "to".  The biggest thing this
     * function does is it makes sure that the directory tree is constructed within 
     * the destination folder.
     * @param from The root folder that the file or folder is being copied from.
     * @param subpath The actual path of the file or folder to copy.
     * @param to the destination folder.
     */
    inline void copy_path(const path& from, const path& subpath, const path& to)
    {
        using boost::filesystem::is_directory;
        using boost::filesystem::is_regular_file;
        using boost::filesystem::is_symlink;
        using boost::filesystem::copy;
        using boost::filesystem::exists;
        
        path newdest(to / split(from.parent_path(), subpath).second);
        
        copy_directories(from, subpath.parent_path(), to);
        if(is_directory(newdest.parent_path()) && 
                !exists(newdest)) copy(subpath, newdest);
    }
    
    
}

/* regular_iterator member functions: */
namespace filesystem
{
    regular_iterator::regular_iterator() : 
            beg_path(),
            it()
    {
    }
    
    regular_iterator::regular_iterator(const path& s) : 
            beg_path(s),
            it(s)
    {
    }
    
    regular_iterator::regular_iterator(const regular_iterator& i) : 
            beg_path(i.beg_path),
            it(i.it)
    {
    }
    
    regular_iterator::~regular_iterator()
    {
    }
    
    regular_iterator& regular_iterator::operator=(const regular_iterator& i)
    {
        if(this != &i)
        {
            this->it = i.it;
            this->beg_path = i.beg_path;
        }
        return *this;
    }
    
    bool regular_iterator::operator!=(const regular_iterator& i) const
    {
        return (this->it != i.it);
    }
    
    bool regular_iterator::operator==(const regular_iterator& i) const
    {
        return (this->it == i.it);
    }
    
    directory_entry& regular_iterator::operator*()
    {
        return *(this->it);
    }
    
    directory_entry* regular_iterator::operator->()
    {
        return &(*(this->it));
    }
    
    void regular_iterator::swap(regular_iterator& i)
    {
        regular_iterator tempit(i);
        i = (*this);
        (*this) = tempit;
    }
    
    regular_iterator& regular_iterator::operator++()
    {
        using boost::filesystem::is_directory;
        using boost::filesystem::is_symlink;
        
        if(this->end()) return *this;
        ++(this->it);
        return *this;
    }
    
    regular_iterator regular_iterator::operator++(int)
    {
        regular_iterator newit(*this);
        ++(*this);
        return newit;
    }
    
    /**
     * @return true if at end.
     */
    bool regular_iterator::end() const
    {
        return (this->it == boost::filesystem::directory_iterator());
    }
    
    
}

/* recursive_iterator member functions: */
namespace filesystem
{
    recursive_iterator::recursive_iterator() : 
            it(),
            beg_path()
    {
    }
    
    recursive_iterator::recursive_iterator(const boost::filesystem::path& s) : 
            it(s),
            beg_path(s)
    {
    }
    
    recursive_iterator::recursive_iterator(const recursive_iterator& r) : 
            it(r.it),
            beg_path(r.beg_path)
    {
    }
    
    recursive_iterator::~recursive_iterator()
    {
    }
    
    recursive_iterator& recursive_iterator::operator=(const recursive_iterator& r)
    {
        if(this != &r)
        {
            this->it = r.it;
            this->beg_path = r.beg_path;
        }
        return *this;
    }
    
    bool recursive_iterator::operator!=(const recursive_iterator& i) const
    {
        return (this->it != i.it);
    }
    
    bool recursive_iterator::operator==(const recursive_iterator& i) const
    {
        return (this->it == i.it);
    }
    
    directory_entry& recursive_iterator::operator*()
    {
        return *(this->it);
    }
    
    directory_entry* recursive_iterator::operator->()
    {
        return &(*(this->it));
    }
    
    void recursive_iterator::swap(recursive_iterator& i)
    {
        recursive_iterator tempit(i);
        i = (*this);
        (*this) = tempit;
    }
    
    recursive_iterator& recursive_iterator::operator++()
    {
        using boost::filesystem::is_directory;
        using boost::filesystem::is_symlink;
        
        if(this->end()) return *this;
        
        try
        {
            if(is_directory(this->it->path()) && is_symlink(this->it->path()))
            {
                this->it.no_push();
            }
            ++(this->it);
        }
        catch(...)
        {
            this->it.no_push();
            ++(this->it);
        }
        return *this;
    }
    
    recursive_iterator recursive_iterator::operator++(int)
    {
        recursive_iterator newit(*this);
        ++(*this);
        return newit;
    }
    
    /**
     * @return true if at end.
     */
    bool recursive_iterator::end() const
    {
        return (this->it == boost::filesystem::recursive_directory_iterator());
    }
    
    
}

namespace filesystem
{
    copy_iterator::copy_iterator() : 
            recursive_iterator()
    {
    }
    
    copy_iterator::copy_iterator(const path& from, const path& to) : 
            recursive_iterator(from),
            source(from),
            dest(to)
    {
        using boost::filesystem::is_directory;
        using boost::filesystem::filesystem_error;
        using boost::system::error_code;
        
        error_code ec;
        if(is_directory(to / from.filename())) throw filesystem_error("Path exists!", from, to, ec);
    }
    
    copy_iterator::copy_iterator(const copy_iterator& c) : 
            recursive_iterator(c),
            source(c.source),
            dest(c.dest)
    {
    }
    
    copy_iterator::~copy_iterator()
    {
    }
    
    copy_iterator& copy_iterator::operator=(const copy_iterator& c)
    {
        if(this != &c)
        {
            recursive_iterator::operator=(c);
            this->source = c.source;
            this->dest = c.dest;
        }
        return *this;
    }
    
    copy_iterator& copy_iterator::operator++()
    {
        copy_path(this->source, this->it->path(), this->dest);
        recursive_iterator::operator++();
        return *this;
    }
    
    copy_iterator copy_iterator::operator++(int)
    {
        copy_iterator newit(*this);
        ++(*this);
        return newit;
    }
    
    
}

