#include "gtest.h"
#include "func.h"

TEST(Fac, Positive)
{
    EXPECT_EQ(6, ttt::fac(3));
}
