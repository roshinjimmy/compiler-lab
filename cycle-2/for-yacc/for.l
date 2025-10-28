%{
#include "for.tab.h"
%}

%%
"for"       return FOR;
[0-9]+      return NUMBER;
[a-zA-Z_][a-zA-Z0-9_]* return ID;
[ \t\n]     ;
.           return yytext[0];
%%

int yywrap() { return 1; }