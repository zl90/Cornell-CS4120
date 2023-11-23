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
%token DIVIDE EQUALS GTE LTE HIGH_MULTIPLY NOT_EQUALS PLUS COMMA MINUS UNDERSCORE MULTIPLY MODULO ASSIGNMENT AND OR BANG GT LT L_BRACKETS R_BRACKETS L_CURLY_BRACES R_CURLY_BRACES L_PARENS R_PARENS SEMICOLON COLON
%token ERROR
%token NEWLINE

%type <character> CHARACTER
%type <string> STRING
%type <integer> INTEGER
%type <keyword> USE IF WHILE ELSE RETURN LENGTH INT BOOL TRUE FALSE
%type <id> ID
%type <symbol> DIVIDE EQUALS GTE LTE HIGH_MULTIPLY NOT_EQUALS PLUS COMMA MINUS UNDERSCORE MULTIPLY MODULO ASSIGNMENT AND OR BANG GT LT L_BRACKETS R_BRACKETS L_CURLY_BRACES R_CURLY_BRACES L_PARENS R_PARENS SEMICOLON COLON
%type <error> ERROR

%union {
    char *character;
    char *string;
    int integer;
    char *id;
    char *error;
}

%%

prog:
    stmts
;

stmts:
    | stmt NEWLINE stmts
;

stmt:
    IF expression stmt {printf("SUCCESS!!!!");}
    | expression {printf("Ended up at a statement...");}
;

expression: 
    ID operator primary_expression
    | primary_expression
    | L_PARENS expression R_PARENS
;

primary_expression:
    ID
    | STRING
    | INTEGER
    | CHARACTER
;

operator:
    comparison_operator
    | arithmetic_operator
    | logical_operator
    | ASSIGNMENT
;

comparison_operator:
    EQUALS
    | GTE
    | LTE
    | GT
    | LT
    | NOT_EQUALS
;

arithmetic_operator:
    PLUS
    | MINUS
    | DIVIDE
    | HIGH_MULTIPLY
    | MULTIPLY
    | MODULO
;

logical_operator:
    AND
    | OR
;

punctuation:
    COMMA
    | L_BRACKETS
    | R_BRACKETS
    | L_CURLY_BRACES
    | R_CURLY_BRACES
    | L_PARENS
    | R_PARENS
    | SEMICOLON
    | COLON
;

symbol:
    operator
    | punctuation
    | UNDERSCORE
    | BANG
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