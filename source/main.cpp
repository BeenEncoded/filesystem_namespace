#ifndef UNIT_TEST_PROG
#include <iostream>

int main(int, char**)
{
    using std::cout;
    using std::endl;
    
    cout<< "This is not a program.  If you build the \"testing\" target, you \
may run the unit tests for this library abstraction.  :)"<< endl;
    return 0;
}

#else


#include "test/unit_testing.hpp"

int main(int, char**)
{
    return run_tests();
}

#endif
