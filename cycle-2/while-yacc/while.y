%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token WHILE ID NUMBER RELOP INC DEC

%%
stmt:
    WHILE '(' condition ')' stmt_body { printf("Valid WHILE statement\n"); }
    ;

condition:
    ID RELOP ID
  | ID RELOP NUMBER
  | NUMBER RELOP ID
  ;

stmt_body:
      ID ';'
    | ID INC ';'
    | ID DEC ';'
    | '{' body '}'
    ;

body:
      ID ';'
    | ID INC ';'
    | ID DEC ';'
    | body ID ';'
    | body ID INC ';'
    | body ID DEC ';'
    ;
%%

void yyerror(const char *s) {
    printf("Invalid WHILE statement\n");
}

int main() {
    printf("Enter a WHILE statement:\n");
    yyparse();
    return 0;
}
