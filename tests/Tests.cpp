#include <gtest/gtest.h>

#include "../src/Geometry.hpp"

TEST(geometry_test, quadratic_roots_test)
{
    const DoublePair result1 = quadratic_roots(1,6,5);
    EXPECT_EQ(result1.first.value() , -1 );
    EXPECT_EQ(result1.second.value(), -5 );

    const DoublePair result2 = quadratic_roots(-2,1,3);
    EXPECT_EQ(result2.first.value() , -1);
    EXPECT_EQ(result2.second.value(), 1.5);

    const DoublePair result3 = quadratic_roots(-4,8,0);
    EXPECT_EQ(result3.first.value() , 0);
    EXPECT_EQ(result3.second.value(), 2);

    const DoublePair result4 = quadratic_roots(1,0,0);
    EXPECT_EQ(result4.first.value() , 0);
    EXPECT_FALSE(result4.second.has_value());
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}