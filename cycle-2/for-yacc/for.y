%{
#include <stdio.h>
int yylex();
void yyerror(char *s) { printf("Invalid FOR statement\n"); }
%}

%token FOR ID NUMBER

%%
stmt: FOR '(' init ';' cond ';' inc ')' { printf("Valid FOR statement\n"); }
    ;

init: ID '=' NUMBER
    | ID '=' ID  
    | /* empty */
    ;

cond: ID '<' NUMBER
    | ID '>' NUMBER
    | ID '>' ID
    | ID '<' ID
    | ID '<' '=' NUMBER
    | ID '>' '=' NUMBER
    | /* empty */
    ;

inc: ID '+' '+'
   | ID '-' '-'
   | /* empty */
   ;
%%

int main() {
    printf("Enter FOR statement: ");
    yyparse();
    return 0;
}