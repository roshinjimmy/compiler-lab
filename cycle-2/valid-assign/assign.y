%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token SEMICOLON EQUALS
%token NUMBER ID

%%
stmt : ID EQUALS expr SEMICOLON   { printf("Valid assignment statement.\n"); }
    ;
expr:
      ID
    | NUMBER
    ;
%%
int main(){
    printf("Enter a variable assignment stmt");
    if(yyparse()==0){
        printf("Parsing completed successfully");
    }
}
void yyerror(const char *s){
    printf("Error:%s\n",s);
}