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
    stmt semicolon_optional
    | stmt semicolon_optional newlines
    | stmt semicolon_optional newlines stmts {printf("STATEMENTS!!");}
;

newlines: 
    NEWLINE 
    | NEWLINE newlines
;

semicolon_optional:
    | SEMICOLON
;

stmt:
    assignment_stmt
    | return_stmt
    | function_call_stmt
    | function_declaration_stmt
    | import_directive
    /*| if_stmt
    | if_else_stmt
    | while_loop_stmt
    | block_stmt */
;

assignment_stmt:
    set_assignment_stmt
    | basic_assignment_stmt
;

set_assignment_stmt: /* Not finished */
    ID ASSIGNMENT L_CURLY_BRACES primary_expression_list R_CURLY_BRACES
;

basic_assignment_stmt: /* Not finished */
    ID ASSIGNMENT primary_expression
;

return_stmt: /* Not finished */
    RETURN
    | RETURN primary_expression_list
;

function_call_stmt: /* Not finished */
    ID L_PARENS primary_expression_list R_PARENS
    | ID L_PARENS R_PARENS
;

function_declaration_stmt: /* Not finished */
    ID L_PARENS primary_expression_list R_PARENS block_stmt
    | ID L_PARENS R_PARENS block_stmt
;

import_directive:
    USE ID
;

if_stmt: /* Not finished */
    IF expression block_stmt
;

if_else_stmt: /* Not finished */
    IF expression block_stmt ELSE block_stmt
;

while_loop_stmt: /* Not finished */
    WHILE expression block_stmt
;

block_stmt: /* Not finished */
    L_CURLY_BRACES newlines stmts R_CURLY_BRACES
    | L_CURLY_BRACES newlines R_CURLY_BRACES
;

primary_expression_list: /* Not finished */
    primary_expression
    | primary_expression COMMA primary_expression_list 
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
    | function_call_stmt
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