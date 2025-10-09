%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token IF ELSE ID NUMBER RELOP ASSIGN

%%
program:
    stmt { printf("Valid IF statement\n"); }
    | stmt ';' { printf("Valid IF statement\n"); }
    ;

stmt:
   IF '(' condition ')' stmt ELSE stmt
   | IF '(' condition ')' stmt
   | '{' stmt_list '}'
   | ID ASSIGN expr
   | ID
   ;
   
stmt_list:
      /* empty */
    | stmt_list stmt
    ;
    
condition:
      ID RELOP ID
    | ID RELOP NUMBER
    | NUMBER RELOP ID
    | NUMBER RELOP NUMBER
    ;
    
expr:
      ID
    | NUMBER
    ;
%%

void yyerror(const char *s) {
    printf("Invalid IF statement\n");
}

int main() {
    printf("Enter an if-else statement:\n");
    yyparse();
    return 0;
}