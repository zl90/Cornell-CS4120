/* This is a flex rule file. This gets fed to the
flex program and it generates a scanner program */

%{
int row_num = 0, col_num = 0;
%}

DIGIT       [0-9]
INTEGER     (-)?{DIGIT}+
NEWLINE     \n
CHARACTER   '([^'\\\n]|\\.)'|'\''|'\\'
STRING      "[^\"]*"
SYMBOL      (\/|==|>=|<=|\*\>|!=|\+|-|\*|%|=|&|\||!|>|<|\{|\}|\[|\]|\(|\)|;|\:)
KEYWORD     use|if|while|else|return|length|int|bool|true|false
ID          [a-zA-Z_][a-zA-Z0-9_]*

%%
{NEWLINE}       {++row_num; col_num = 0;}
.               {++col_num;}
[[:space:]]+    { /* Ignore spaces */ }
{CHARACTER}     {printf("%d:%d character %s\n", row_num, col_num, yytext);}
{STRING}        {printf("%d:%d string %s\n", row_num, col_num, yytext);}
{INTEGER}       {printf("%d:%d integer %s\n", row_num, col_num, yytext);}
{KEYWORD}       {printf("%d:%d %s\n", row_num, col_num, yytext);}
{ID}            {printf("%d:%d id %s\n", row_num, col_num, yytext);}
{SYMBOL}        {printf("%d:%d %s\n", row_num, col_num, yytext);}
%%

yywrap()
{
}

int main() {
    yylex();
    return 0;
}