%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token IF ELSE ID NUMBER RELOP

%%
stmt:
      IF '(' condition ')' stmt                        /* simple if */
    | IF '(' condition ')' stmt ELSE stmt               /* if-else */
    | '{' stmt_list '}'                                 /* block */
    | ID ';'                                            /* simple statement */
    ;

stmt_list:
      stmt
    | stmt_list stmt
    ;

condition:
      ID RELOP ID
    | ID RELOP NUMBER
    | NUMBER RELOP ID
    ;

%%
void yyerror(const char *s) {
    printf("Invalid IF statement\n");
}

int main() {
    printf("Enter an IF statement:\n");
    yyparse();
    return 0;
}
