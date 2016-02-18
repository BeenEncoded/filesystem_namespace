#ifdef UNIT_TEST_PROG
#include <boost/filesystem.hpp>
#include <iostream>

#include "copy.hpp"
#include "filesystem.hpp"

namespace test
{
    void copy()
    {
        using filesystem::copy_iterator;
        using std::cout;
        using std::endl;
        using boost::filesystem::filesystem_error;
        
        for(copy_iterator it("/run/media/jonathan/1fa7ab9a-3cab-46e0-a711-63e67b6e9f63/C++/Current_Projects/filesystem_namespace", 
                "../../../.."); 
                !it.end(); ++it);
    }
    
    
}

#endif
