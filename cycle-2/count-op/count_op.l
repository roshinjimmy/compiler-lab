%{
    #include "count_op.tab.h"
%}

%%
[a-zA-Z]+   {return ID;}
[0-9]+      {yylval = atoi(yytext); return NUMBER;}
[\t ]        ;
\n          {return EOL;}
"+"         {return PLUS;}
"-"         {return MINUS;}
"*"         {return MULT;}
"/"         {return DIV;}
.           {printf("Unknown Character:%s\n",yytext);}
%%

int yywrap(void){
    return 1;
}