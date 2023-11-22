/* This is a flex rule file. This gets fed to the
flex program and it generates a scanner program */

%{
#include <stdio.h>
#include <string.h>
#include "bison_input.tab.h"

int row_num = 1, col_num = 1;

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
%}

DIGIT           [0-9]
INTEGER         {DIGIT}+
HEXADECIMAL     [0-9a-fA-F]{1,6}
NEWLINE         \n
CHARACTER       '([^'\\\n]|\\.)'|'\''|'\\'|'\\x\{{HEXADECIMAL}\}'
STRING          \"[^\"^\n]*\"
SYMBOL          (\/|==|>=|<=|\*\>\>|!=|\+|,|-|_|\*|%|=|&|\||!|>|<|\{|\}|\[|\]|\(|\)|;|\:)
KEYWORD         use|if|while|else|return|length|int|bool|true|false
ID              [a-zA-Z][a-zA-Z0-9_\']*
COMMENT         \/\/[^\n]*
EMPTY_CHAR      \'\'
INVALID_CHAR    \'[^\'\n]*
INVALID_STRING  \"[^\"\n]*
INVALID_SYMBOL  [\?#@`]

%%
{CHARACTER}         {col_num += yyleng; yylval.character = strdup(remove_quotations(handle_unicode_escape_sequences(yytext))); return CHARACTER;}
{STRING}            {col_num += yyleng; yylval.string = strdup(remove_quotations(handle_unicode_escape_sequences(yytext))); return STRING;}
{INTEGER}           {col_num += yyleng; yylval.integer = atoi(yytext); yylval.row_num = row_num; yylval.col_num = col_num; return INTEGER;}
{KEYWORD}           {col_num += yyleng; yylval.keyword = strdup(yytext); return KEYWORD;}
{ID}                {col_num += yyleng; yylval.id = strdup(yytext); return ID;}
{SYMBOL}            {col_num += yyleng; yylval.symbol = strdup(yytext); return SYMBOL;}
{EMPTY_CHAR}        {yylval.error = strdup("error:empty character literal"); return ERROR; yyterminate();}
{INVALID_CHAR}      {yylval.error = strdup("error:Invalid character literal"); return ERROR; yyterminate();}
{INVALID_STRING}    {yylval.error = strdup("error:Invalid string literal"); return ERROR; yyterminate();}
{INVALID_SYMBOL}    {yylval.error = strdup("error:Invalid symbol"); return ERROR; yyterminate();}
{COMMENT}           {/* Ignore coments */}
{NEWLINE}           {++row_num; col_num = 1; return NEWLINE;}
.                   {++col_num;}
%%

int yywrap()
{
}