%{
#include "y.tab.h"
%}

%%
while           { return WHILE; }
[a-zA-Z_][a-zA-Z0-9_]*    { return ID; }
[0-9]+                    { return NUMBER; }
"=="|"!="|"<"|">"|"<="|">="   { return RELOP; }
[ \t\n]+                  { /* ignore whitespace */ }
.                         { return yytext[0]; }
%%

int yywrap() { return 1; }
