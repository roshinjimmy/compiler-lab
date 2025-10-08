%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token WHILE ID NUMBER RELOP

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
  | '{' ID ';' '}'
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
