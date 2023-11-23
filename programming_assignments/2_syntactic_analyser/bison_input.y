%{
    #include <stdio.h>

    #define YYDEBUG 1 // DEBUGGING

    int yylex();
    int yyerror(char *s);
%}

%token CHARACTER
%token STRING
%token INTEGER
%token ID
%token USE IF WHILE ELSE RETURN LENGTH INT BOOL TRUE FALSE
%token FWD_SLASH EQUALS GTE LTE MULT_SHIFT NOT_EQUALS PLUS COMMA MINUS UNDERSCORE MULTIPLY MODULO ASSIGNMENT AND PIPE BANG GT LT L_BRACKETS R_BRACKETS L_CURLY_BRACES R_CURLY_BRACES L_PARENS R_PARENS SEMICOLON COLON
%token ERROR
%token NEWLINE

%type <character> CHARACTER
%type <string> STRING
%type <integer> INTEGER
%type <keyword> USE IF WHILE ELSE RETURN LENGTH INT BOOL TRUE FALSE
%type <id> ID
%type <symbol> FWD_SLASH EQUALS GTE LTE MULT_SHIFT NOT_EQUALS PLUS COMMA MINUS UNDERSCORE MULTIPLY MODULO ASSIGNMENT AND PIPE BANG GT LT L_BRACKETS R_BRACKETS L_CURLY_BRACES R_CURLY_BRACES L_PARENS R_PARENS SEMICOLON COLON
%type <error> ERROR

%union {
    char *character;
    char *string;
    int integer;
    char *keyword;
    char *id;
    char *symbol;
    char *error;
    int length;
    int row_num;
    int col_num;
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
        printf("That is a number: %d", $1);
    }
    | CHARACTER {
        printf("Character: %s", $1);
    }
    | symbol
    | keyword
    | ERROR
;

symbol:
    FWD_SLASH
    | EQUALS
    | GTE
    | LTE
    | MULT_SHIFT
    | NOT_EQUALS
    | PLUS
    | COMMA
    | MINUS
    | UNDERSCORE
    | MULTIPLY
    | MODULO
    | ASSIGNMENT
    | AND
    | PIPE
    | BANG
    | GT
    | LT
    | L_BRACKETS
    | R_BRACKETS
    | L_CURLY_BRACES
    | R_CURLY_BRACES
    | L_PARENS
    | R_PARENS
    | SEMICOLON
    | COLON
;

keyword:
    USE
    | IF
    | WHILE
    | ELSE
    | RETURN
    | LENGTH
    | INT
    | BOOL
    | TRUE
    | FALSE
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