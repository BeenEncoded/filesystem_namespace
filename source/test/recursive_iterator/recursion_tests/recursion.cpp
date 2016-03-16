#ifdef UNIT_TEST_PROG
#include <boost/filesystem.hpp>
#include <iostream>

#include "filesystem.hpp"
#include "recursion.hpp"

namespace
{
    std::string remove_quotes(const std::string&);
    
    
    inline std::string remove_quotes(const std::string& s)
    {
        std::string temps(s);
        
        if(temps.find("\"") == 0)
        {
            temps.erase(temps.begin());
        }
        if(temps.rfind("\"") == (temps.size() - 1))
        {
            temps.erase(temps.size() - 1);
        }
        return temps;
    }
    
    
}

namespace test
{
    void recursion()
    {
        using boost::filesystem::current_path;
        using std::cout;
        using std::endl;
        using filesystem::recursive_iterator;
        
        for(recursive_iterator it(current_path().string()); it != recursive_iterator(); ++it)
        {
            cout<< remove_quotes(it->path().string())<< endl;
        }
    }
    
    
}

#endif
