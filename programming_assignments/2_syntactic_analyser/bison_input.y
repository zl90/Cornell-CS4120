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
%token DIVIDE EQUALS GTE LTE HIGH_MULTIPLY NOT_EQUALS PLUS COMMA MINUS UNDERSCORE MULTIPLY MODULO ASSIGNMENT AND OR BANG GT LT L_BRACKETS R_BRACKETS L_CURLY_BRACES R_CURLY_BRACES L_PARENS R_PARENS COLON
%token ERROR

%type <character> CHARACTER
%type <string> STRING
%type <integer> INTEGER
%type <keyword> USE IF WHILE ELSE RETURN LENGTH INT BOOL TRUE FALSE
%type <id> ID
%type <symbol> DIVIDE EQUALS GTE LTE HIGH_MULTIPLY NOT_EQUALS PLUS COMMA MINUS UNDERSCORE MULTIPLY MODULO ASSIGNMENT AND OR BANG GT LT L_BRACKETS R_BRACKETS L_CURLY_BRACES R_CURLY_BRACES L_PARENS R_PARENS COLON
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
    stmt {printf("Statement parsed!!!");}
    | stmt stmts {printf("STATEMENTS!!");}
;

stmt:
    assignment_stmt
    | return_stmt {printf("RETURN STATEMENT PARSED!!!!!");}
    | function_call_stmt
    | function_declaration_stmt
    | import_directive
    | if_stmt
    | if_else_stmt
    | block_stmt
    | while_loop_stmt
;

assignment_stmt:    
    declaration_element_list assignment_stmt_rhs
;

declaration_element_list:
    declaration_element
    | declaration_element COMMA declaration_element_list
;

assignment_stmt_rhs: /* Not finished */
    | ASSIGNMENT primary_expression_list
    | ASSIGNMENT expression_list
;

return_stmt: /* Not finished */
    empty_return_stmt
    | singular_return_stmt
    | list_return_stmt
;

empty_return_stmt:
    RETURN
;

singular_return_stmt:
    empty_return_stmt primary_expression
;

list_return_stmt:
    singular_return_stmt COMMA primary_expression_list
;

function_call_stmt: /* Not finished */
    ID L_PARENS primary_expression_list R_PARENS
    | ID L_PARENS R_PARENS
;

set:
    L_CURLY_BRACES primary_expression_list R_CURLY_BRACES
;

function_declaration_stmt: /* Not finished */
    ID L_PARENS declaration_element_list R_PARENS block_stmt
    | ID L_PARENS R_PARENS block_stmt
    | ID L_PARENS declaration_element_list R_PARENS COLON type_list block_stmt
    | ID L_PARENS R_PARENS COLON type_list block_stmt
;

declaration_element:
    UNDERSCORE
    | ID
    | array_id
    | ID COLON type
;

array_id:
    array_reference
    | array_2d_reference
;

array_reference:
    ID array_subscript
;

array_2d_reference:
    array_reference array_subscript
;

type_list:
    type
    | type COMMA type_list
;

type:
    simple_type
    | array_type
    | array_2d_type
;

simple_type:
    BOOL
    | INT
;

array_type:
    simple_type array_subscript
;

array_2d_type:
    array_type array_subscript
;

array_subscript:
    L_BRACKETS array_subcript_element R_BRACKETS
;

array_subcript_element:
    | ID
    | INTEGER
    | function_call_stmt
;

import_directive:
    USE ID
;

if_stmt: /* Not finished */
    IF if_while_expression block_stmt
;

if_else_stmt: /* Not finished */
    if_stmt ELSE block_stmt
;

while_loop_stmt: /* Not finished */
    WHILE if_while_expression block_stmt
;

block_stmt: /* Not finished */
    L_CURLY_BRACES stmts R_CURLY_BRACES
    | L_CURLY_BRACES R_CURLY_BRACES
;

primary_expression_list: /* Not finished */
    primary_expression
    | primary_expression COMMA primary_expression_list 
;

if_while_expression: 
    ID operator primary_expression
    | primary_expression
    | L_PARENS if_while_expression R_PARENS
;

expression_list:
    expression
    | expression COMMA expression_list
;

expression:
    primary_expression operator primary_expression
    | primary_expression operator expression
;

primary_expression:
    ID
    | STRING
    | INTEGER
    | CHARACTER
    | TRUE
    | FALSE
    | function_call_stmt
    | set
    | array_id
;

operator:
    comparison_operator
    | arithmetic_operator
    | logical_operator
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