#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <gtest/gtest.h>

// int add(int a, int b)
// {
//     return a + b;
// }

// TEST(add, positive)
// {
//     ASSERT_EQ(10, add(5, 5));
// }

std::string extract_filename_from_path(std::string input)
{
    std::istringstream iss(input);

    std::vector<std::string> parts;

    std::string part;
    while (std::getline(iss, part, '/'))
    {
        parts.push_back(part);
    }

    if (!parts.empty())
    {
        return parts.back();
    }
    else
    {
        return "";
    }
}

void print_synopsis()
{
    std::cout << "Printing synopsis...\n";
}

void lex(const char *input_filename, const char *output_dir)
{
    std::cout << "Lexing file: " << input_filename << std::endl;
}

std::vector<std::string> handle_cli_args(const int length, const char *const args[])
{
    try
    {
        if (length == 1 || (length == 2 && std::strcmp(args[1], "--help") == 0))
        {
            print_synopsis();
            std::vector<std::string> empty_vector;
            return empty_vector;
        }

        std::vector<std::string> input_filenames;
        std::string output_dir = "";

        if (length >= 3)
        {
            int i = 1;
            bool is_lex_mode = false;
            bool is_dirname_mode = false;

            do
            {
                const std::string arg = args[i];

                if (arg == "--test")
                {
                    i++;
                    continue;
                }

                if (arg == "--lex")
                {
                    is_lex_mode = true;
                    is_dirname_mode = false;
                    i++;
                    continue;
                }
                else if (arg == "-D")
                {
                    is_lex_mode = false;
                    is_dirname_mode = true;
                    i++;
                    continue;
                }

                if (is_lex_mode)
                {
                    if (arg == "-D" && input_filenames.empty())
                    {
                        throw std::invalid_argument("Error: invalid command line arguments supplied. Include the --help flag to see valid options.");
                    }
                    else if (arg == "-D")
                    {
                        is_lex_mode = false;
                        is_dirname_mode = true;
                        i++;
                        continue;
                    }
                    else
                    {
                        input_filenames.push_back(arg);
                    }
                }
                else if (is_dirname_mode)
                {
                    output_dir = arg;
                    is_dirname_mode = false;
                }

                i++;

            } while (i < length);
        }
        else
        {
            throw std::invalid_argument("Error: invalid command line arguments supplied. Include the --help flag to see valid options.");
        }

        std::vector<std::string> result;

        for (std::string item : input_filenames)
        {
            std::string extracted_filename = extract_filename_from_path(item);

            if (!output_dir.empty())
            {
                result.push_back(output_dir + extracted_filename);
            }
            else
            {
                result.push_back(extracted_filename);
            }
        }

        return input_filenames;
    }
    catch (std::invalid_argument const &ex)
    {
        std::cout << ex.what() << '\n';
    }
}

TEST(test, CompletesLexModeOnly)
{
    const char *const args[] = {"etac", "--lex", "./../a.eta", "./b.eta"};
    auto output = handle_cli_args(4, args);
    ASSERT_EQ(output, {"a.eta", "b.eta"});
}

// TEST(handle_cli_args, CompletesLexModeAndDirMode)
// {
//     const char *const args[] = {"etac", "--lex", "./../a.eta", "./b.eta", "-D", "../"};
//     auto output = handle_cli_args(6, args);
//     EXPECT_EQ(output, {"../a.eta", "../b.eta"});
// }

bool should_run_tests(const int length, const char *const args[])
{
    for (int i = 0; i < length; i++)
    {
        if (std::strcmp(args[i], "--test") == 0)
        {
            return true;
        }
    }

    return false;
}

int main(int argc, char *argv[])
{
    int local_argc = 1;
    char *local_argv[] = {"./build/etac"};
    ::testing::InitGoogleTest(&local_argc, local_argv);

    // handle_cli_args(argc, argv);

    if (should_run_tests(argc, argv))
    {
        return RUN_ALL_TESTS();
    }
    return 1;
}