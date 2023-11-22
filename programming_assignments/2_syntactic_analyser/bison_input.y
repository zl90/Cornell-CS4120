%{
    #include <stdio.h>

    #define YYDEBUG 1 // DEBUGGING

    int yylex();
    int yyerror(char *s);
%}

%token CHARACTER STRING INTEGER KEYWORD ID SYMBOL ERROR NEWLINE

%type <character> CHARACTER
%type <string> STRING
%type <integer> INTEGER
%type <keyword> KEYWORD
%type <id> ID
%type <symbol> SYMBOL
%type <error> ERROR

%union {
    char *character;
    char *string;
    int integer;
    char *keyword;
    char *id;
    char *symbol;
    char *error;
}

%%

prog:
    stmts
;

stmts:
    | stmt NEWLINE stmts

stmt:
    STRING {
        printf("Hello to you too %s", $1);
    }
    | INTEGER {
        printf("That is a number");
    }
    | ERROR
;

%%

int yyerror(char *s)
{
	printf("Syntax Error on line %s\n", s);
	return 0;
}


int main() {
    yydebug = 1; // DEBUGGING
    yyparse();

    return 0;
}