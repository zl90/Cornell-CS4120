%{
    #include <stdio.h>

    int yylex();
    int yyerror(char *s);
%}

%token STRING NUM OTHER SEMICOLON PIC

%type <name> STRING
%type <number> NUM
%type <name> PIC

%union {
    char name[20];
    char * character;
    int number;
}

%%

prog:
    stmts
;

stmts:
    | stmt SEMICOLON stmts

stmt:
    STRING {
        printf("Hello to you too %s", $1);
    }
    | NUM {
        printf("That is a number");
    }
    | OTHER
;

%%

int main() {
    yyparse();

    return 0;
}