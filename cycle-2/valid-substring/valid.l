%{
#include <stdio.h>
%}

%%
.*[Rr][Oo][Ss][Hh].*    { printf("Invalid String\n"); }
.*                      { printf("Valid String\n"); }
%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}