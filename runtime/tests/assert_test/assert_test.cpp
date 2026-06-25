#include <gtest/gtest.h>

#include <Core/Assert.h>

TEST(assert_test, success)
{
    EX_ASSERT(0 == 0, "0 always equal 0");
}

TEST(assert_test, fail)
{
    EXPECT_DEATH(EX_ASSERT(1 == 0, "1 isn't equal 0"), "Assertion '1 == 0' failed. Message: 1 isn't equal 0");
}