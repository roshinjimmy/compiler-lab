%{
#include "varval.tab.h"
#include <stdlib.h>
%}
%%
";"     {return SEMICOLON;}
"="     {return EQUALS;};
[0-9]+  {yylval = atoi(yytext);return NUMBER;}
[a-zA-Z_][a-zA-Z0-9_]* {return ID;}
[\t\n]+  ;
.         { return yytext[0]; }
%%
int yywrap() {return 1;}