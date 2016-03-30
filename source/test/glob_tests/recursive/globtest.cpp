#ifdef UNIT_TEST_PROG
#include <boost/filesystem.hpp>
#include <iostream>

#include "filesystem.hpp"
#include "globtest.hpp"

namespace testing
{
    bool recursive_test()
    {
        using filesystem::recursive_glob;
        using boost::filesystem::current_path;
        using boost::filesystem::path;
        using std::cout;
        using std::endl;
        
        for(recursive_glob it((current_path() / path("..")), "**.[ch]pp$"); !it.end(); ++it)
        {
            cout<< *it<< endl;
        }
        return true;
    }
}

#endif
