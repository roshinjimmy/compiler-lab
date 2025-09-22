%{
#include "calc.tab.h"
%}

%%
[0-9]+          { yylval = atoi(yytext); return NUMBER; }
[ \t]           ;       // Ignore whitespace
\n              { return EOL; }
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MULT; }
"/"             { return DIV; }
"("             { return LPAREN; }
")"             { return RPAREN; }
.               { printf("Unknown character: %s\n", yytext); }
%%

int yywrap(void) {
    return 1;
}
