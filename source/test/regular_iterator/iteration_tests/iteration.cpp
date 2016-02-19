#ifdef UNIT_TEST_PROG
#include <boost/filesystem.hpp>
#include <iostream>

#include "filesystem.hpp"
#include "iteration.hpp"


namespace test
{
    void iteration()
    {
        using namespace filesystem;
        using boost::filesystem::current_path;
        using std::cout;
        using std::endl;
        
        for(regular_iterator it(current_path().string()); !it.end(); ++it)
        {
            cout<< it.value()<< endl;
        }
    }
    
    
}

#endif
