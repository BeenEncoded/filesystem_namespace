#ifdef UNIT_TEST_PROG
#include <boost/filesystem.hpp>
#include <iostream>

#include "filesystem.hpp"
#include "recursion.hpp"

namespace test
{
    void recursion()
    {
        using boost::filesystem::current_path;
        using std::cout;
        using std::endl;
        using filesystem::recursive_iterator;
        
        for(recursive_iterator it(current_path().string()); !it.end(); ++it)
        {
            cout<< it.value()<< endl;
        }
    }
    
    
}

#endif
