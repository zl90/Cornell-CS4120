#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <optional>
#include <gtest/gtest.h>

#define INVALID_ARGUMENT_EXCEPTION std::invalid_argument("Error: invalid command line arguments supplied. Include the --help flag to see valid options.")

const std::string LEXER_PATH = "./build/lexer";
const std::string LEXER_OUTPUT_FILE_EXTENSION = ".lexed";

struct LexInput
{
    std::string input_filename;
    std::string output_filename;

    LexInput(std::string input_filename, std::string output_filename)
    {
        this->input_filename = input_filename;
        this->output_filename = output_filename;
    }
};

enum TokenType
{
    ID,
    INTEGER,
    CHARACTER,
    STRING,
    SYMBOL,
    KEYWORD
};

struct Token
{
    TokenType type;
    std::optional<std::string> value;

    Token(TokenType type, std::optional<std::string> value)
    {
        this->type = type;
        this->value = value;
    }
};

std::vector<LexInput> handle_cli_args(const int, const char *const[]);

TEST(HandleCliArgs, CompletesLexModeOnly)
{
    const char *const args[] = {"etac", "--lex", "./../a.eta", "./b.eta"};
    auto input = handle_cli_args(4, args);

    LexInput info1 = LexInput("./../a.eta", "a.lexed");
    LexInput info2 = LexInput("./b.eta", "b.lexed");

    std::vector<LexInput> expected_output = {info1, info2};

    for (size_t i = 0; i < input.size(); ++i)
    {
        ASSERT_EQ(input[i].input_filename, expected_output[i].input_filename);
        ASSERT_EQ(input[i].output_filename, expected_output[i].output_filename);
    }
}

TEST(HandleCliArgs, CompletesLexModeFollowedByDirMode)
{
    const char *const args[] = {"etac", "--lex", "./../a.eta", "./b.eta", "-D", "./build/"};
    auto input = handle_cli_args(6, args);

    LexInput info1 = LexInput("./../a.eta", "./build/a.lexed");
    LexInput info2 = LexInput("./b.eta", "./build/b.lexed");

    std::vector<LexInput> expected_output = {info1, info2};

    ASSERT_EQ(input.size(), expected_output.size());

    for (size_t i = 0; i < input.size(); ++i)
    {
        ASSERT_EQ(input[i].input_filename, expected_output[i].input_filename);
        ASSERT_EQ(input[i].output_filename, expected_output[i].output_filename);
    }
}

TEST(HandleCliArgs, CompletesDirModeFollowedByLexMode)
{
    const char *const args[] = {"etac", "-D", "./build", "--lex", "./../a.eta", "./b.eta"};
    auto input = handle_cli_args(6, args);

    LexInput info1 = LexInput("./../a.eta", "./build/a.lexed");
    LexInput info2 = LexInput("./b.eta", "./build/b.lexed");

    std::vector<LexInput> expected_output = {info1, info2};

    ASSERT_EQ(input.size(), expected_output.size());

    for (size_t i = 0; i < input.size(); ++i)
    {
        ASSERT_EQ(input[i].input_filename, expected_output[i].input_filename);
        ASSERT_EQ(input[i].output_filename, expected_output[i].output_filename);
    }
}

TEST(HandleCliArgs, ThrowsOnMissingLexFlag)
{
    const char *const args[] = {"etac", "-D", "./build"};

    ASSERT_THROW(handle_cli_args(3, args), std::invalid_argument);
}

TEST(HandleCliArgs, ThrowsOnMissingFilenames)
{
    const char *const args[] = {"etac", "--lex", "-D", "./build"};

    ASSERT_THROW(handle_cli_args(4, args), std::invalid_argument);
}

TEST(HandleCliArgs, ThrowsOnIncorrectFlags)
{
    const char *const args[] = {"etac", "--abc"};

    ASSERT_THROW(handle_cli_args(2, args), std::invalid_argument);
}

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

std::string remove_file_extension(std::string input_filename)
{
    std::istringstream iss(input_filename);

    std::vector<std::string> parts;

    std::string part;
    while (std::getline(iss, part, '.'))
    {
        parts.push_back(part);
    }

    if (!parts.empty())
    {
        return parts.front();
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

std::vector<Token> lex(const LexInput &info)
{

    std::cout << "Lexing input file: " << info.input_filename << '\n';
    std::cout << "Writing output file: " << info.output_filename << '\n';

    std::vector<Token> empty_vector;
    return empty_vector;
}

std::vector<LexInput> handle_cli_args(const int length, const char *const args[])
{
    try
    {
        if (length == 1 || (length == 2 && std::strcmp(args[1], "--help") == 0))
        {
            print_synopsis();
            std::vector<LexInput> empty_vector;
            return empty_vector;
        }

        std::vector<std::string> input_filenames;
        std::string output_dir = "";
        bool has_lex_flag = false;

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
                    if (is_dirname_mode && output_dir.empty())
                    {
                        throw INVALID_ARGUMENT_EXCEPTION;
                    }

                    has_lex_flag = true;
                    is_lex_mode = true;
                    is_dirname_mode = false;
                    i++;
                    continue;
                }
                else if (arg == "-D")
                {
                    if (is_lex_mode && input_filenames.empty())
                    {
                        throw INVALID_ARGUMENT_EXCEPTION;
                    }

                    is_lex_mode = false;
                    is_dirname_mode = true;
                    i++;
                    continue;
                }

                if (is_lex_mode)
                {
                    input_filenames.push_back(arg);
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
            throw INVALID_ARGUMENT_EXCEPTION;
        }

        if (input_filenames.empty() || !has_lex_flag)
        {
            throw INVALID_ARGUMENT_EXCEPTION;
        }

        if (!output_dir.empty() && output_dir.back() != '/')
        {
            output_dir += "/";
        }

        std::vector<LexInput> result;

        for (std::string input_filename : input_filenames)
        {
            std::string extracted_filename = extract_filename_from_path(input_filename);
            std::string filename_without_extension = remove_file_extension(extracted_filename);
            std::string output_filename = output_dir + filename_without_extension + LEXER_OUTPUT_FILE_EXTENSION;
            LexInput lex_info = LexInput(input_filename, output_filename);
            result.push_back(lex_info);
        }

        return result;
    }
    catch (std::invalid_argument const &exception)
    {
        std::cout << exception.what() << '\n';

        throw std::invalid_argument(exception.what());

        std::vector<LexInput> empty_vector;
        return empty_vector;
    }
}

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

    if (should_run_tests(argc, argv))
    {
        return RUN_ALL_TESTS();
    }
    else
    {
        std::vector<LexInput> lex_jobs = handle_cli_args(argc, argv);

        for (LexInput lex_job : lex_jobs)
        {
            lex(lex_job);
        }
    }

    return 0;
}