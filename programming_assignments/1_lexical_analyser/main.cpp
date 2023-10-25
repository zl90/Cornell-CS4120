#include <iostream>
#include <string>
#include <gtest/gtest.h>

int add(int a, int b)
{
    return a + b;
}

TEST(add, positive)
{
    ASSERT_EQ(10, add(5, 5));
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}