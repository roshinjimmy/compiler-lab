%{
#include <stdio.h>
%}

%%
.*Rosh.*    { printf("Invalid String\n"); return 0; }
.*rosh.*    { printf("Invalid String\n"); return 0; }
.*          { printf("Valid String"); }
%%

int main(void) {
    yylex();
    return 0;
}
