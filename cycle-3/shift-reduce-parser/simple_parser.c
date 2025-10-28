#include <stdio.h>
#include <string.h>

char stack[100], input[100];
int top = -1;

// Grammar: S -> S+S | S-S | (S) | i

void print_state(int ip, char *action) {
    for(int i=0; i<=top; i++) printf("%c", stack[i]);
    printf("\t\t%s\t\t%s\n", input+ip, action);
}

int reduce() {
    // S -> i
    if(stack[top] == 'i') {
        stack[top] = 'S';
        return 1;
    }
    // S -> S+S
    if(top >= 2 && stack[top] == 'S' && stack[top-1] == '+' && stack[top-2] == 'S') {
        top -= 2;
        stack[top] = 'S';
        return 1;
    }
    // S -> S-S  
    if(top >= 2 && stack[top] == 'S' && stack[top-1] == '-' && stack[top-2] == 'S') {
        top -= 2;
        stack[top] = 'S';
        return 1;
    }
    // S -> (S)
    if(top >= 2 && stack[top] == ')' && stack[top-1] == 'S' && stack[top-2] == '(') {
        top -= 2;
        stack[top] = 'S';
        return 1;
    }
    return 0;
}

int main() {
    printf("Enter expression: ");
    scanf("%s", input);
    
    printf("\nStack\t\tInput\t\tAction\n");
    printf("----------------------------------------\n");
    
    int ip = 0;  // input pointer
    stack[++top] = '$';  // stack bottom
    
    // Process input until end
    while(input[ip] != '\0') {
        // Shift current input symbol
        stack[++top] = input[ip++];
        print_state(ip, "SHIFT");
        
        // Keep reducing as much as possible
        while(reduce()) {
            print_state(ip, "REDUCE");
        }
    }
    
    // Final check: stack should be $S
    if(top == 1 && stack[top] == 'S') {
        printf("\nExpression Accepted!\n");
    } else {
        printf("\nExpression Rejected!\n");
        printf("Final stack: ");
        for(int i=0; i<=top; i++) printf("%c", stack[i]);
        printf("\n");
    }
    
    return 0;
}