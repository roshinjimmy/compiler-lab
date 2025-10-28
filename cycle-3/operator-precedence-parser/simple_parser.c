#include <stdio.h>
#include <string.h>

char stack[100], input[100];
int top = -1;

// Precedence table for: + - * / ( ) i #
char prec[8][8] = {
    // +    -    *    /    (    )    i    #
    {'>', '>', '<', '<', '<', '>', '<', '>'}, // +
    {'>', '>', '<', '<', '<', '>', '<', '>'}, // -
    {'>', '>', '>', '>', '<', '>', '<', '>'}, // *
    {'>', '>', '>', '>', '<', '>', '<', '>'}, // /
    {'<', '<', '<', '<', '<', '=', '<', ' '}, // (
    {'>', '>', '>', '>', ' ', '>', ' ', '>'}, // )
    {'>', '>', '>', '>', ' ', '>', ' ', '>'}, // i
    {'<', '<', '<', '<', '<', ' ', '<', 'a'}  // #
};

int idx(char c)
{
    char *s = "+-*/()i#";   
    for (int i = 0; s[i]; i++)
        if (s[i] == c)
            return i;
    return -1;
}

int reduce()
{
    // Handle i -> E (identifier to expression)
    if (stack[top] == 'i')
    {
        stack[top] = 'E';
        return 1;
    }
    // Handle E+E, E-E, E*E, E/E -> E
    if (top >= 2 && stack[top] == 'E' &&
        (stack[top - 1] == '+' || stack[top - 1] == '-' ||
         stack[top - 1] == '*' || stack[top - 1] == '/') &&
        stack[top - 2] == 'E')
    {
        top -= 2;
        stack[top] = 'E';
        return 1;
    }
    // Handle (E) -> E
    if (top >= 2 && stack[top] == ')' && stack[top - 1] == 'E' && stack[top - 2] == '(')
    {
        top -= 2;
        stack[top] = 'E';
        return 1;
    }
    return 0;
}

// Function to get the top terminal from stack (ignores E)
char getTopTerminal()
{
    for (int i = top; i >= 0; i--)
    {
        if (stack[i] != 'E')
        {
            return stack[i];
        }
    }
    return '#'; // Default to # if no terminal found
}

int main()
{
    printf("Enter expression: ");
    scanf("%s", input);

    // Convert letters to 'i' and add #
    int len = strlen(input);
    for (int i = 0; i < len; i++)
    {
        if (input[i] >= 'a' && input[i] <= 'z')
        {
            input[i] = 'i';
        }
    }
    strcat(input, "#");

    stack[++top] = '#';
    int ip = 0;
    int step = 1;

    printf("\nProcessing: %s\n", input);
    printf("Step\tStack\t\tInput\t\tAction\n");
    printf("------------------------------------------------\n");

    while (1)
    {
        // Display current state
        printf("%d\t%s\t\t%s\t\t", step++, stack, input + ip);

        char st = getTopTerminal(); // Get top terminal (ignore E)
        char in = input[ip];

        if (in == '\0')
        {
            printf("Error: Unexpected end\n");
            break;
        }

        int row = idx(st);
        int col = idx(in);

        if (row == -1)
        {
            printf("Error: Invalid stack top %c\n", st);
            break;
        }
        if (col == -1)
        {
            printf("Error: Invalid input %c\n", in);
            break;
        }

        char rel = prec[row][col];

        if (rel == '<' || rel == '=')
        {
            stack[++top] = in;
            ip++;
            printf("Shift %c\n", in);
        }
        else if (rel == '>')
        {
            if (reduce())
            {
                printf("Reduce\n");
            }
            else
            {
                printf("Error: Cannot reduce\n");
                break;
            }
        }
        else if (rel == 'a')
        {
            printf("Accept\n");
            printf("\nExpression is valid!\n");
            break;
        }
        else
        {
            printf("Error: No relation %c %c\n", st, in);
            break;
        }

        // Safety check
        if (step > 50)
        {
            printf("Error: Too many steps\n");
            break;
        }
    }
    return 0;
}