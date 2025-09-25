#include <stdio.h>
#include <string.h>

#define MAX 100

// Global variables
char stack[MAX];
char input[MAX];
int top = -1;

// Precedence table:
//        +    *    (    )   id   #
char precedenceTable[6][6] = {
    {'>', '<', '<', '>', '<', '>'}, // +
    {'>', '>', '<', '>', '<', '>'}, // *
    {'<', '<', '<', '=', '<', ' '}, // (
    {'>', '>', ' ', '>', ' ', '>'}, // )
    {'>', '>', ' ', '>', ' ', '>'}, // id
    {'<', '<', '<', ' ', '<', 'a'}  // #
};

// Function declarations
int getIndex(char *symbol);
int topTerminalIndex();
void shift(char *symbol);
int reduce();
char getRelation(const char *stackTop, const char *current);

// Get index in precedence table
int getIndex(char *symbol) {
    if (strcmp(symbol, "+") == 0) return 0;
    if (strcmp(symbol, "*") == 0) return 1;
    if (strcmp(symbol, "(") == 0) return 2;
    if (strcmp(symbol, ")") == 0) return 3;
    if (strcmp(symbol, "id") == 0) return 4;
    if (strcmp(symbol, "#") == 0) return 5;
    return -1;
}

// Find top-most terminal in the stack
int topTerminalIndex() {
    for (int i = top; i >= 0; i--) {
        if (stack[i] == '+' || stack[i] == '*' || stack[i] == '(' ||
            stack[i] == ')' || stack[i] == '#' || stack[i] == 'i') {
            if (stack[i] == 'i' && stack[i + 1] == 'd') {
                return getIndex("id");
            } else {
                char temp[2] = {stack[i], '\0'};
                return getIndex(temp);
            }
        }
    }
    return -1;
}

// Shift operation
void shift(char *symbol) {
    if (strcmp(symbol, "id") == 0) {
        stack[++top] = 'i';
        stack[++top] = 'd';
    } else {
        stack[++top] = symbol[0];
    }
}

// Reduce operation
int reduce() {
    // id -> E
    if (stack[top] == 'd' && stack[top - 1] == 'i') {
        top--;
        stack[top] = 'E';
        return 1;
    }
    // E + E
    if (stack[top] == 'E' && stack[top - 1] == '+' && stack[top - 2] == 'E') {
        top -= 2;
        stack[top] = 'E';
        return 1;
    }
    // E * E
    if (stack[top] == 'E' && stack[top - 1] == '*' && stack[top - 2] == 'E') {
        top -= 2;
        stack[top] = 'E';
        return 1;
    }
    // ( E )
    if (stack[top] == ')' && stack[top - 1] == 'E' && stack[top - 2] == '(') {
        top -= 2;
        stack[top] = 'E';
        return 1;
    }
    return 0;
}

// Get precedence relation
char getRelation(const char *stackTop, const char *current) {
    int row = getIndex((char *)stackTop);
    int col = getIndex((char *)current);
    if (row == -1 || col == -1) return ' ';
    return precedenceTable[row][col];
}

// Main function
int main() {
    char rawInput[MAX];
    char current[3];

    printf("Enter expression ending with #: ");
    fgets(rawInput, MAX, stdin);

    // Remove spaces from input
    int j = 0;
    for (int i = 0; rawInput[i] != '\0'; i++) {
        if (rawInput[i] != ' ' && rawInput[i] != '\n') {
            input[j++] = rawInput[i];
        }
    }
    input[j] = '\0';

    int ip = 0;
    top = 0;
    stack[top] = '#';

    int step = 1;

    // Table header
    printf("\n%-5s %-20s %-20s %-15s\n", "Step", "Stack", "Input", "Action");
    printf("---------------------------------------------------------------\n");

    while (1) {
        // Prepare input display
        char displayInput[MAX];
        strcpy(displayInput, input + ip);

        // Prepare stack display
        char displayStack[MAX] = "";
        for (int i = 0; i <= top; i++) {
            char s[3];
            s[0] = stack[i];
            s[1] = '\0';
            if (stack[i] == 'i' && stack[i + 1] == 'd') {
                strcpy(s, "id");
                i++; // skip 'd'
            }
            strcat(displayStack, s);
        }

        // Get stack top terminal
        char stackTop[3];
        int idx = topTerminalIndex();

        if (idx == 4) strcpy(stackTop, "id");
        else if (idx == 5) strcpy(stackTop, "#");
        else if (idx == 0) strcpy(stackTop, "+");
        else if (idx == 1) strcpy(stackTop, "*");
        else if (idx == 2) strcpy(stackTop, "(");
        else if (idx == 3) strcpy(stackTop, ")");
        else strcpy(stackTop, " ");

        // Get current input symbol
        if (input[ip] == 'i' && input[ip + 1] == 'd') {
            strcpy(current, "id");
        } else {
            current[0] = input[ip];
            current[1] = '\0';
        }

        char relation = getRelation(stackTop, current);

        if (relation == '<' || relation == '=') {
            shift(current);
            if (strcmp(current, "id") == 0) ip += 2;
            else ip++;

            printf("%-5d %-20s %-20s %-15s\n", step++, displayStack, displayInput, "Shift");
        } else if (relation == '>') {
            if (!reduce()) {
                printf("%-5d %-20s %-20s %-15s\n", step++, displayStack, displayInput, "Error: Reduce");
                printf("Error: Cannot reduce\n");
                return 1;
            } else {
                printf("%-5d %-20s %-20s %-15s\n", step++, displayStack, displayInput, "Reduce");
            }
        } else if (relation == 'a') {
            printf("%-5d %-20s %-20s %-15s\n", step++, displayStack, displayInput, "Accept");
            printf("\nExpression Accepted!\n");
            return 0;
        } else {
            printf("%-5d %-20s %-20s %-15s\n", step++, displayStack, displayInput, "Error: Invalid rel");
            printf("Error: Invalid relation\n");
            return 1;
        }
    }

    return 0;
}
