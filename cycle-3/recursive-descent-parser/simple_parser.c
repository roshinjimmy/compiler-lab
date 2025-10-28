#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

const char *input;
int pos = 0;
char lookahead;

void error()
{
    printf("Error at position %d\n", pos);
    exit(1);
}

void advance()
{
    lookahead = input[pos++];
}

void match(char expected)
{
    if (lookahead == expected)
        advance();
    else
        error();
}

// Grammar: E → T E', E' → + T E' | ε, T → F T', T' → * F T' | ε, F → (E) | digit
void E();
void E_();
void T();
void T_();
void F();

void E()
{
    T();
    E_();
}
void E_()
{
    if (lookahead == '+')
    {
        match('+');
        T();
        E_();
    }
}
void T()
{
    F();
    T_();
}
void T_()
{
    if (lookahead == '*')
    {
        match('*');
        F();
        T_();
    }
}
void F()
{
    if (lookahead == '(')
    {
        match('(');
        E();
        match(')');
    }
    else if (isdigit(lookahead))
        match(lookahead);
    else
        error();
}

int main()
{
    char expr[100];
    printf("Enter expression: ");
    scanf("%s", expr);

    input = expr;
    advance();
    E();

    if (lookahead == '\0')
        printf("Valid expression!\n");
    else
        printf("Invalid expression!\n");

    return 0;
}