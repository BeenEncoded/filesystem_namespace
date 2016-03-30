#ifdef UNIT_TEST_PROG
#ifndef RECURSIVE_TEST_HPP_INCLUDED
#define RECURSIVE_TEST_HPP_INCLUDED
#include <unittest++/UnitTest++.h>

#include "globtest.hpp"

TEST(recursive_glob_test)
{
    bool success(testing::recursive_test());
    CHECK(success);
}

#endif
#endif
