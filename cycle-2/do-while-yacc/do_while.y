%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token DO WHILE ID NUMBER RELOP

%%
stmt:
    DO stmt_body WHILE '(' condition ')' ';' { printf("Valid DO-WHILE statement\n"); }
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
    printf("Invalid DO-WHILE statement\n");
}

int main() {
    printf("Enter a DO-WHILE statement:\n");
    yyparse();
    return 0;
}
