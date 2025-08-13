%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token FOR INT LPAREN RPAREN SEMICOLON ASSIGN LT LE GT GE EQ NE INC DEC
%token NUMBER ID

%left LT LE GT GE EQ NE
%right ASSIGN
%left INC DEC

%%
stmt : FOR LPAREN init_opt SEMICOLON cond_opt SEMICOLON inc_opt RPAREN
       { printf("Valid FOR statement syntax\n"); }
     ;

init_opt : /* empty */
         | expr
         | declaration
         ;

cond_opt : /* empty */
         | expr
         ;

inc_opt : /* empty */
        | expr
        ;

declaration : INT ID ASSIGN NUMBER
            | INT ID
            ;

expr : assignment
     | comparison
     | incdec
     ;

assignment : ID ASSIGN NUMBER
           | ID ASSIGN ID
           ;

comparison : ID relop NUMBER
           | ID relop ID
           ;

incdec : ID INC
       | ID DEC
       ;

relop : LT
      | LE
      | GT
      | GE
      | EQ
      | NE
      ;
%%

int main() {
    printf("Enter a FOR statement:\n");
    if (yyparse() == 0)
        printf("Parsing completed successfully.\n");
    return 0;
}

void yyerror(const char *s) {
    printf("Error: %s\n", s);
}
