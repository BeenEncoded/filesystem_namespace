#ifdef UNIT_TEST_PROG
#ifndef ITERATION_TESTS_TEST_HPP_INCLUDED
#define ITERATION_TESTS_TEST_HPP_INCLUDED
#include <unittest++/UnitTest++.h>

#include "iteration.hpp"

SUITE(regular_iterator_test_suite)
{
    TEST(regular_iterator_iteration_test)
    {
        test::iteration();
    }
    
    
}

#endif
#endif
