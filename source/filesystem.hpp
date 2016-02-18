#ifndef UTILITY_FILESYSTEM_HPP_INCLUDED
#define UTILITY_FILESYSTEM_HPP_INCLUDED
#include <boost/filesystem.hpp>
#include <string>

namespace filesystem
{
    class iterator;
    class regular_iterator;
    class copy_iterator;
    
    /**
     * @class iterator
     * @author Jonathan Whitlock
     * @date 02/16/2016
     * @file filesystem.hpp
     * @brief An abstract base class outlining the basic functions a filesystem
     * iterator should have.
     */
    class iterator
    {
    public:
        virtual iterator& operator++() = 0;
        virtual const boost::filesystem::path& value() const = 0;
        virtual bool end() const = 0;
    };
    
    /**
     * @class regular_iterator
     * @author Jonathan Whitlock
     * @date 02/16/2016
     * @file filesystem.hpp
     * @brief A non-recursive filesystem iterator wrapper for the 
     * boost directory_iterator.
     */
    class regular_iterator : public iterator
    {
    public:
        explicit regular_iterator();
        regular_iterator(const boost::filesystem::path&);
        
        virtual regular_iterator& operator++();
        
        const boost::filesystem::path& value() const;
        bool end() const;
        
    protected:
        boost::filesystem::path beg_path;
        boost::filesystem::directory_iterator it;
    };
    
    /**
     * @class recursive_iterator
     * @author Jonathan Whitlock
     * @date 02/16/2016
     * @file filesystem.hpp
     * @brief A recursive filesystem iterator wrapper for the
     * boost recursive_directory_iterator.
     */
    class recursive_iterator : public iterator
    {
    public:
        explicit recursive_iterator();
        recursive_iterator(const boost::filesystem::path&);
        
        virtual recursive_iterator& operator++();
        
        const boost::filesystem::path& value() const;
        bool end() const;
        
    protected:
        boost::filesystem::recursive_directory_iterator it;
        boost::filesystem::path beg_path;
        
    };
    
    /**
     * @class copy_iterator
     * @author Jonathan Whitlock
     * @date 02/16/2016
     * @file filesystem.hpp
     * @brief Recursively copies a folder into another folder.
     */
    class copy_iterator : public recursive_iterator
    {
    public:
        explicit copy_iterator();
        copy_iterator(const boost::filesystem::path&, const boost::filesystem::path&);
        
        copy_iterator& operator++();
        
    private:
        boost::filesystem::path source, dest;
    };
    
    
}

#endif
