#ifdef UNIT_TEST_PROG
#include <boost/filesystem.hpp>
#include <iostream>

#include "filesystem.hpp"
#include "globtest.hpp"

namespace testing
{
    bool glob()
    {
        using filesystem::glob;
        using boost::filesystem::current_path;
        using boost::filesystem::path;
        
        for(glob it((current_path() / path("../../..")), "**.txt$"); !it.end(); ++it)
        {
            std::cout<< *it<< std::endl;
        }
        return true;
    }
    
}

#endif
