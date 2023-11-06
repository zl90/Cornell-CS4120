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
std::string read_from_file(std::string);

TEST(Lex, LexesAddFile)
{
    LexInput lex_input = LexInput("./test_input/add.eta", "./build/add.lexed");
    std::string input = lex(lex_input);

    std::string
        expected_output = read_from_file("./test_solutions/add.lexedsol");

    ASSERT_EQ(input, expected_output);
}

TEST(Lex, LexesArrayInitFile)
{
    LexInput lex_input = LexInput("./test_input/arrayinit.eta", "./build/arrayinit.lexed");
    std::string input = lex(lex_input);

    std::string
        expected_output = read_from_file("./test_solutions/arrayinit.lexedsol");

    ASSERT_EQ(input, expected_output);
}

TEST(Lex, LexesArrayInit2File)
{
    LexInput lex_input = LexInput("./test_input/arrayinit2.eta", "./build/arrayinit2.lexed");
    std::string input = lex(lex_input);

    std::string
        expected_output = read_from_file("./test_solutions/arrayinit2.lexedsol");

    ASSERT_EQ(input, expected_output);
}

TEST(Lex, LexesBeautyFile)
{
    LexInput lex_input = LexInput("./test_input/beauty.eta", "./build/beauty.lexed");
    std::string input = lex(lex_input);

    std::string
        expected_output = read_from_file("./test_solutions/beauty.lexedsol");

    ASSERT_EQ(input, expected_output);
}

TEST(Lex, LexesEx1File)
{
    LexInput lex_input = LexInput("./test_input/ex1.eta", "./build/ex1.lexed");
    std::string input = lex(lex_input);

    std::string
        expected_output = read_from_file("./test_solutions/ex1.lexedsol");

    ASSERT_EQ(input, expected_output);
}

TEST(Lex, LexesEx2File)
{
    LexInput lex_input = LexInput("./test_input/ex2.eta", "./build/ex2.lexed");
    std::string input = lex(lex_input);

    std::string
        expected_output = read_from_file("./test_solutions/ex2.lexedsol");

    ASSERT_EQ(input, expected_output);
}

TEST(Lex, LexesGcdFile)
{
    LexInput lex_input = LexInput("./test_input/gcd.eta", "./build/gcd.lexed");
    std::string input = lex(lex_input);

    std::string
        expected_output = read_from_file("./test_solutions/gcd.lexedsol");

    ASSERT_EQ(input, expected_output);
}

TEST(Lex, LexesInsertionSortFile)
{
    LexInput lex_input = LexInput("./test_input/insertionsort.eta", "./build/insertionsort.lexed");
    std::string input = lex(lex_input);

    std::string
        expected_output = read_from_file("./test_solutions/insertionsort.lexedsol");

    ASSERT_EQ(input, expected_output);
}

TEST(Lex, LexesMdarraysFile)
{
    LexInput lex_input = LexInput("./test_input/mdarrays.eta", "./build/mdarrays.lexed");
    std::string input = lex(lex_input);

    std::string
        expected_output = read_from_file("./test_solutions/mdarrays.lexedsol");

    ASSERT_EQ(input, expected_output);
}

TEST(Lex, LexesRatAddFile)
{
    LexInput lex_input = LexInput("./test_input/ratadd.eta", "./build/ratadd.lexed");
    std::string input = lex(lex_input);

    std::string
        expected_output = read_from_file("./test_solutions/ratadd.lexedsol");

    ASSERT_EQ(input, expected_output);
}

TEST(Lex, LexesRatAddUseFile)
{
    LexInput lex_input = LexInput("./test_input/ratadduse.eta", "./build/ratadduse.lexed");
    std::string input = lex(lex_input);

    std::string
        expected_output = read_from_file("./test_solutions/ratadduse.lexedsol");

    ASSERT_EQ(input, expected_output);
}

TEST(Lex, LexesSpec1File)
{
    LexInput lex_input = LexInput("./test_input/spec1.eta", "./build/spec1.lexed");
    std::string input = lex(lex_input);

    std::string
        expected_output = read_from_file("./test_solutions/spec1.lexedsol");

    ASSERT_EQ(input, expected_output);
}

TEST(Lex, LexesSpec2File)
{
    LexInput lex_input = LexInput("./test_input/spec2.eta", "./build/spec2.lexed");
    std::string input = lex(lex_input);

    std::string
        expected_output = read_from_file("./test_solutions/spec2.lexedsol");

    ASSERT_EQ(input, expected_output);
}

TEST(Lex, LexesSpec3File)
{
    LexInput lex_input = LexInput("./test_input/spec3.eta", "./build/spec3.lexed");
    std::string input = lex(lex_input);

    std::string
        expected_output = read_from_file("./test_solutions/spec3.lexedsol");

    ASSERT_EQ(input, expected_output);
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
    std::cout << "\e[1mNAME\e[0m\n\tetac - the Eta Compiler\n\n\e[1mSYNOPSIS\n\tetac\e[0m [OPTIONS] [FILE]...\n\n\e[1mDESCRIPTION\e[0m\n\tReads in input files of the .eta format and produces output files in the .lexed format containing the results of a lexical scan.\n\n\e[1mOPTIONS\n\t--help\e[0m\n\t\tdisplay the help menu\n\n\t\e[1m--lex\e[0m [FILE]\n\t\tperform a lexical scan on the filenames [FILE]\n\n\t\e[1m-D\e[0m [DIR]\n\t\tspecify the directory to store the output files. If not specified, files are outputted to the current working directory\n\n\e[1mEXAMPLES\e[0m\n\t./etac -D ./build --lex hello_world.eta foo.eta bar.eta\n\t./etac --lex hello_world.eta" << std::endl;
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

std::string read_from_file(std::string filename)
{
    std::ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        throw std::filesystem::filesystem_error("Invalid input filename: " + filename, std::error_code());
        return "";
    }

    std::string result = "";
    std::string line;
    while (std::getline(inputFile, line))
    {
        result += line + "\n";
    }

    inputFile.close();

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