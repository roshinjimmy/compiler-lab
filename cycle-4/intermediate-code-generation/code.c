#include <stdio.h>
#include <string.h>

void gen_code_for_operator(char *inp, char operator, char *reg)
{
    int i = 0, j = 0;
    char temp[100];
    while (inp[i] != '\0')
    {
        if (inp[i] == operator)
        {
            char op1 = inp[i - 1];
            char op2 = inp[i + 1];
            printf("%c\t%c\t%c\t%c\n", operator, *reg, op1, op2);
            temp[j - 1] = *reg; // Replace operand1 with result register
            i += 2;             // Skip operator and operand2
            (*reg)--;           // Move to next register
        }
        else
        {
            temp[j++] = inp[i++];
        }
    }
    temp[j] = '\0'; // Proper null-termination
    strcpy(inp, temp); // Update original string
}

void gen_code(char *inp)
{
    char reg = 'Z'; // Temporary register starting from Z
    gen_code_for_operator(inp, '/', &reg);
    gen_code_for_operator(inp, '*', &reg);
    gen_code_for_operator(inp, '+', &reg);
    gen_code_for_operator(inp, '-', &reg);
    gen_code_for_operator(inp, '=', &reg);
}

int main()
{
    char inp[100];
    printf("Enter expression: ");
    scanf("%s", inp);
    printf("Oprtr\tDestn\tOp1\tOp2\n");
    gen_code(inp);
    return 0;
}
