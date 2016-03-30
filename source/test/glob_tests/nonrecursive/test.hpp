#ifdef UNIT_TEST_PROG
#ifndef GLOB_TESTS_NONRECURSIVE_TEST_HPP_INCLUDED
#define GLOB_TESTS_NONRECURSIVE_TEST_HPP_INCLUDED
#include <unittest++/UnitTest++.h>

#include "globtest.hpp"

TEST(nonrecursive_glob_test)
{
    bool success(testing::glob());
    CHECK(success);
}

#endif
#endif
