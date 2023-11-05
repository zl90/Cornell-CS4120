#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <filesystem>
#include <cstring>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <system_error>
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

std::vector<LexInput> handle_cli_args(const int, const char *const[]);
std::string lex(const LexInput &);

TEST(Lex, LexesValidInputFile)
{
    LexInput lex_input1 = LexInput("./test_input/test.eta", "./build/test.lexed");
    std::string input1 = lex(lex_input1);

    std::string
        expected_output1 = {"1:1 int\n1:5 id main\n1:9 ;\n"};

    ASSERT_EQ(input1, expected_output1);

    LexInput lex_input2 = LexInput("./test_input/test2.eta", "./build/test2.lexed");
    std::string input2 = lex(lex_input2);

    std::string
        expected_output2 = {"1:1 bool\n1:6 id x\n2:1 id a\n2:2 :\n2:3 int\n2:6 [\n2:7 ]\n2:9 =\n2:11 string \nasdf\n\n"};

    ASSERT_EQ(input2, expected_output2);
}

TEST(Lex, ThrowsOnInvalidInputFile)
{
    LexInput lex_input = LexInput("./test_input/test1.eta", "./build/test.lexed");
    ASSERT_THROW(lex(lex_input), std::filesystem::filesystem_error);
}

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

std::string execute_command(const char *command)
{
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command, "r"), pclose);
    if (!pipe)
    {
        throw std::runtime_error("Incorrect input filename");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }
    return result;
}

void write_to_file(std::string filename, std::string data)
{
    std::ofstream file;
    file.open(filename);
    file << data;
    file.close();
}

std::string lex(const LexInput &info)
{
    if (!std::filesystem::exists(info.input_filename))
    {
        throw std::filesystem::filesystem_error("Invalid input filename", std::error_code());
    }

    std::string result = "";

    std::cout << "Lexing input file: " << info.input_filename << '\n';
    std::string command = LEXER_PATH + "<" + info.input_filename;
    result = execute_command(command.c_str());

    std::cout << "Writing output file: " << info.output_filename << '\n';
    write_to_file(info.output_filename, result);

    return result;
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