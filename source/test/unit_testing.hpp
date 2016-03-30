#ifdef UNIT_TEST_PROG
#ifndef TEST_UNIT_TESTING_HPP_INCLUDED
#define TEST_UNIT_TESTING_HPP_INCLUDED
#include <unittest++/UnitTest++.h>

//tests:
//#include "test/regular_iterator/test.hpp"
//#include "test/recursive_iterator/test.hpp"
//#include "test/copy_iterator/test.hpp"
#include "test/glob_tests/glob_tests.hpp"

namespace
{
    int run_tests();
    
    
    
    inline int run_tests()
    {
        return UnitTest::RunAllTests();
    }
    
    
}

#endif
#endif
