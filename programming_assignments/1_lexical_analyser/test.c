#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *remove_quotations(char *str)
{
    int str_length = strlen(str);

    if (str_length <= 2)
    {
        return "";
    }

    if ((str[0] == '\'' || str[0] == '\"') && (str[str_length - 1] == '\'' || str[str_length - 1] == '\"'))
    {
        for (size_t i = 0; i < str_length; i++)
        {
            // Shift the characters to remove the first character
            str[i] = str[i + 1];
        }

        // Null-terminate the string to remove the last character
        str[str_length - 2] = '\0';
    }

    return str;
}

char *handle_unicode_escape_sequences(char *str)
{
    char *result = (char *)malloc(strlen(str) + 1);
    if (!result)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return "";
    }

    int result_index = 0;
    int i = 0;
    int str_len = strlen(str);

    while (i < str_len)
    {
        if (str[i] == '\\' && str[i + 1] == 'x' && str[i + 2] == '{')
        {
            // Found a potential Unicode escape sequence \x{XXXXXX}
            i += 3; // Move past \x{
            char unicode_hex[7];
            int hex_index = 0;

            // Collect the hexadecimal characters
            while (i < str_len && str[i] != '}' && hex_index < 6)
            {
                unicode_hex[hex_index++] = str[i++];
            }
            unicode_hex[hex_index] = '\0';

            if (i < str_len && str[i] == '}')
            {
                // Valid Unicode escape sequence
                char *end;
                long unicode_value = strtol(unicode_hex, &end, 16);

                if (*end == '\0' && unicode_value >= 32 && unicode_value <= 126)
                {
                    // Valid hexadecimal value
                    result[result_index++] = (char)unicode_value;
                    i++; // Move past }
                }
                else
                {
                    // Not a valid hexadecimal value (or special/unprintable character), copy as is
                    result[result_index++] = '\\';
                    result[result_index++] = 'x';
                    result[result_index++] = '{';
                    for (int j = 0; j < hex_index; j++)
                    {
                        result[result_index++] = unicode_hex[j];
                    }
                }
            }
            else
            {
                // Missing closing curly brace, treat as regular characters
                result[result_index++] = '\\';
                result[result_index++] = 'x';
                for (int j = 0; j < hex_index; j++)
                {
                    result[result_index++] = unicode_hex[j];
                }
            }
        }
        else
        {
            // Copy characters normally
            result[result_index++] = str[i++];
        }
    }

    result[result_index] = '\0';

    return result;
}

int main()
{
    char *input1 = "This is a \\x{48}\\x{65}\\x{6C}\\x{6C}\\x{6F} message.";
    char *input2 = "This is a \\x{48}\\x{65}\\x{6C}\\x{6C}\\x{6F} message.\\x{}";
    char *input3 = "This is a \\x{48}\\x{65}\\x{6C}\\x{6C}\\x{6F} message.\\x{12345}";
    char *input4 = "This is a \\x{48}\\x{65}\\x{6C}\\x{6C}\\x{6F} message.\\x{12A}";
    char *input5 = "This is a \\x{7F}\\x{65}\\x{6C}\\x{6C}\\x{6F} message.\\x{X}";

    char *result1 = handle_unicode_escape_sequences(input1);
    char *result2 = handle_unicode_escape_sequences(input2);
    char *result3 = handle_unicode_escape_sequences(input3);
    char *result4 = handle_unicode_escape_sequences(input4);
    char *result5 = handle_unicode_escape_sequences(input5);

    printf("%s\n", result1);
    printf("%s\n", result2);
    printf("%s\n", result3);
    printf("%s\n", result4);
    printf("%s\n", result5);

    free(result1);
    free(result2);
    free(result3);
    free(result4);
    free(result5);

    // char result6[] = "\"a\"";     // a
    // char result7[] = "\'\'";      // ''
    // char result8[] = "a";         // a
    // char result9[] = "\'abc\'";   // abc
    // char result10[] = "\"aaaa\""; // aaaa
    // char result11[] = "\"\"";     // ""

    // printf("%s\n", remove_quotations(result6));
    // printf("%s\n", remove_quotations(result7));
    // printf("%s\n", remove_quotations(result8));
    // printf("%s\n", remove_quotations(result9));
    // printf("%s\n", remove_quotations(result10));
    // printf("%s\n", remove_quotations(result11));

    return 0;
}
