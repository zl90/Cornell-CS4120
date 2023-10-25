#include <iostream>
#include <string>
#include <cstring>
#include <gtest/gtest.h>

int add(int a, int b)
{
    return a + b;
}

// TEST(add, positive)
// {
//     ASSERT_EQ(10, add(5, 5));
// }

void print_synopsis()
{
    std::cout << "Printing synopsis...\n";
}

void handle_cli_args(const int length, const char *const args[])
{
    if (length == 1 || (length == 2 && std::strcmp(args[1], "--help") == 0))
    {
        print_synopsis();
    }
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    handle_cli_args(argc, argv);
    return RUN_ALL_TESTS();
}