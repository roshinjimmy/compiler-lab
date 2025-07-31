#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10
#define SYMBOLS 10

int n_states, n_symbols;
char symbols[SYMBOLS];

int e_nfa[MAX][SYMBOLS][MAX];
int e_transitions[MAX][MAX];

int e_closure[MAX][MAX];
int visited[MAX];

int nfa[MAX][SYMBOLS][MAX];

int symbolIndex(char ch)
{
    for (int i = 0; i < n_symbols; i++)
    {
        if (symbols[i] == ch)
            return i;
    }
    return -1;
}

void dfs(int state, int root)
{
    for (int i = 0; i < n_states; i++)
    {
        if (e_transitions[state][i] && !visited[i])
        {
            visited[i] = 1;
            e_closure[root][i] = 1;
            dfs(i, root);
        }
    }
}

void computeEClosures()
{
    for (int i = 0; i < n_states; i++)
    {
        for (int j = 0; j < n_states; j++)
            visited[j] = 0;

        visited[i] = 1;
        e_closure[i][i] = 1;
        dfs(i, i);
    }
}

void convertENFAtoNFA()
{
    computeEClosures();

    for (int state = 0; state < n_states; state++)
    {
        for (int s = 0; s < n_symbols; s++)
        {
            int temp[MAX] = {0};

            for (int i = 0; i < n_states; i++)
            {
                if (e_closure[state][i])
                {
                    for (int k = 0; k < n_states; k++)
                    {
                        if (e_nfa[i][s][k])
                        {

                            for (int j = 0; j < n_states; j++)
                            {
                                if (e_closure[k][j])
                                {
                                    temp[j] = 1;
                                }
                            }
                        }
                    }
                }
            }

            for (int j = 0; j < n_states; j++)
            {
                nfa[state][s][j] = temp[j];
            }
        }
    }
}

void printResultingNFA()
{
    printf("\nNFA without ε-transitions:\n");
    for (int i = 0; i < n_states; i++)
    {
        for (int s = 0; s < n_symbols; s++)
        {
            printf("From q%d on '%c': { ", i, symbols[s]);
            for (int j = 0; j < n_states; j++)
            {
                if (nfa[i][s][j])
                    printf("q%d ", j);
            }
            printf("}\n");
        }
    }
}

int main()
{
    int t, to, sym_idx;

    printf("Enter number of states: ");
    scanf("%d", &n_states);

    printf("Enter number of input symbols: ");
    scanf("%d", &n_symbols);

    printf("Enter the input symbols (excluding ε):\n");
    for (int i = 0; i < n_symbols; i++)
    {
        printf("Symbol %d: ", i + 1);
        scanf(" %c", &symbols[i]);
    }

    memset(e_nfa, 0, sizeof(e_nfa));
    memset(e_transitions, 0, sizeof(e_transitions));
    memset(e_closure, 0, sizeof(e_closure));
    memset(nfa, 0, sizeof(nfa));

    printf("\nEnter transitions for each state and symbol:\n");
    for (int i = 0; i < n_states; i++)
    {
        for (int s = 0; s < n_symbols; s++)
        {
            printf("From q%d on '%c': how many transitions? ", i, symbols[s]);
            scanf("%d", &t);
            for (int j = 0; j < t; j++)
            {
                printf("  Enter destination state %d: ", j + 1);
                scanf("%d", &to);
                e_nfa[i][s][to] = 1;
            }
        }
    }

    printf("\nEnter epsilon transitions:\n");
    for (int i = 0; i < n_states; i++)
    {
        printf("From q%d: how many ε-transitions? ", i);
        scanf("%d", &t);
        for (int j = 0; j < t; j++)
        {
            printf("  Enter destination state %d: ", j + 1);
            scanf("%d", &to);
            e_transitions[i][to] = 1;
        }
    }

    convertENFAtoNFA();
    printResultingNFA();

    return 0;
}
