/* This is a flex rule file. This gets fed to the
flex program and it generates a scanner program */

%{
int row_num = 1, col_num = 1;
%}

DIGIT       [0-9]
INTEGER     (-)?{DIGIT}+
NEWLINE     \n
CHARACTER   '([^'\\\n]|\\.)'|'\''|'\\'
STRING      \"[^\"]*\"
SYMBOL      (\/|==|>=|<=|\*\>\>|!=|\+|-|\*|%|=|&|\||!|>|<|\{|\}|\[|\]|\(|\)|;|\:)
KEYWORD     use|if|while|else|return|length|int|bool|true|false
ID          [a-zA-Z_][a-zA-Z0-9_]*
COMMENT     \/\/[^\n]*

%%
{CHARACTER}     {printf("%d:%d character %s\n", row_num, col_num, yytext); col_num += yyleng;}
{STRING}        {printf("%d:%d string %s\n", row_num, col_num, yytext); col_num += yyleng;}
{INTEGER}       {printf("%d:%d integer %s\n", row_num, col_num, yytext); col_num += yyleng;}
{KEYWORD}       {printf("%d:%d %s\n", row_num, col_num, yytext); col_num += yyleng;}
{ID}            {printf("%d:%d id %s\n", row_num, col_num, yytext); col_num += yyleng;}
{SYMBOL}        {printf("%d:%d %s\n", row_num, col_num, yytext); col_num += yyleng;}
{COMMENT}       {/* Ignore coments */}
{NEWLINE}       {++row_num; col_num = 1;}
.               {++col_num;}
%%

yywrap()
{
}

int main() {
    yylex();
    return 0;
}