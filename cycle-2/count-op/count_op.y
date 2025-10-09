%{
   #include <stdio.h>
   #include <stdlib.h>

   int yylex(void);
   int yyerror(const char *msg);
   int count = 0;
%}

%token NUMBER ID PLUS MINUS MULT DIV EOL

%left PLUS MINUS
%left MULT DIV

%%
calclist:
    /* empty */
    | calclist expr EOL {printf("count=%d\n",count);count = 0;}
    | expr EOL {printf("count=%d\n",count);}
    ;
expr:
      NUMBER
     | ID 
     | expr PLUS expr {count = count + 1;}
     | expr MINUS expr {count = count + 1;}
     | expr MULT expr {count = count + 1;}
     | expr DIV expr {count = count + 1;}
     ;
%%
int main(){
    printf("Enter Expression:");
    yyparse();
    return 0;
}

int yyerror(const char *msg){
    fprintf(stderr,"Error:%s\n",msg);
    return 0;
}