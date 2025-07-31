#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int n; 
int e_closure[MAX][MAX]; 
int epsilon[MAX][MAX];

int visited[MAX];

void dfs(int state, int original) {
    for (int i = 0; i < n; i++) {
        if (epsilon[state][i] && !visited[i]) {
            visited[i] = 1;
            e_closure[original][i] = 1;
            dfs(i, original);
        }
    }
}

void find_e_closure() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            visited[j] = 0;

        visited[i] = 1;
        e_closure[i][i] = 1;
        dfs(i, i);
    }
}

void print_e_closure() {
    printf("\nEpsilon-closures of states:\n");
    for (int i = 0; i < n; i++) {
        printf("ε-closure(q%d): {", i);
        for (int j = 0; j < n; j++) {
            if (e_closure[i][j])
                printf("q%d ", j);
        }
        printf("}\n");
    }
}

int main() {
    int i, j, num, state;

    printf("Enter the number of states in the NFA: ");
    scanf("%d", &n);

    printf("Enter epsilon transitions (ε) for each state:\n");
    for (i = 0; i < n; i++) {
        printf("Number of ε-transitions from q%d: ", i);
        scanf("%d", &num);
        for (j = 0; j < num; j++) {
            printf("Enter state %d: ", j + 1);
            scanf("%d", &state);
            epsilon[i][state] = 1;
        }
    }

    find_e_closure();
    print_e_closure();

    return 0;
}
