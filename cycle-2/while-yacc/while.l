%{
#include "y.tab.h"
%}

%%
while                   { return WHILE; }
[a-zA-Z_][a-zA-Z0-9_]*  { return ID; }
[0-9]+                  { return NUMBER; }
"=="|"!="|"<"|">"|"<="|">="  { return RELOP; }
"++"                    { return INC; }
"--"                    { return DEC; }
[ \t\n]+                { /* ignore whitespace */ }
.                       { return yytext[0]; }
%%

int yywrap() { return 1; }
