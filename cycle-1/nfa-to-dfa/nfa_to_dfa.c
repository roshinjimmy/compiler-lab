#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

int nfa[MAX][MAX];
int dfa[100][MAX];
int n_states, n_symbols;
char symbols[MAX];

int dfa_states[100][MAX];
int dfa_state_count = 0;

int stateExists(int stateSet[])
{
    for (int i = 0; i < dfa_state_count; i++)
    {
        int match = 1;
        for (int j = 0; j < n_states; j++)
        {
            if (dfa_states[i][j] != stateSet[j])
            {
                match = 0;
                break;
            }
        }
        if (match)
            return i;
    }
    return -1;
}

void addDFAState(int stateSet[], int fromState, int symbolIndex)
{
    int existing = stateExists(stateSet);
    if (existing == -1)
    {
        for (int i = 0; i < n_states; i++)
            dfa_states[dfa_state_count][i] = stateSet[i];

        dfa[fromState][symbolIndex] = dfa_state_count;
        dfa_state_count++;
    }
    else
    {
        dfa[fromState][symbolIndex] = existing;
    }
}

void computeDFA()
{
    int queue[100], front = 0, rear = 0;
    int used[100] = {0};

    queue[rear++] = 0;
    used[0] = 1;

    while (front < rear)
    {
        int current = queue[front++];

        for (int sym = 0; sym < n_symbols; sym++)
        {
            int newSet[MAX] = {0};

            for (int s = 0; s < n_states; s++)
            {
                if (dfa_states[current][s])
                {
                    for (int t = 0; t < n_states; t++)
                    {
                        if (nfa[s * n_symbols + sym][t])
                        {
                            newSet[t] = 1;
                        }
                    }
                }
            }

            if (stateExists(newSet) == -1)
            {
                addDFAState(newSet, current, sym);
                queue[rear++] = dfa_state_count - 1;
                used[dfa_state_count - 1] = 1;
            }
            else
            {
                int existing = stateExists(newSet);
                dfa[current][sym] = existing;
            }
        }
    }
}

void printDFA()
{
    printf("\nDFA Transition Table:\n");
    for (int i = 0; i < dfa_state_count; i++)
    {
        printf("DFA State %d [", i);
        for (int j = 0; j < n_states; j++)
        {
            if (dfa_states[i][j])
                printf("q%d ", j);
        }
        printf("]:\n");

        for (int sym = 0; sym < n_symbols; sym++)
        {
            printf("  On '%c' -> DFA State %d\n", symbols[sym], dfa[i][sym]);
        }
    }
}

int main()
{
    printf("Enter number of NFA states: ");
    scanf("%d", &n_states);

    printf("Enter number of input symbols: ");
    scanf("%d", &n_symbols);

    printf("Enter input symbols:\n");
    for (int i = 0; i < n_symbols; i++)
    {
        printf("Symbol %d: ", i + 1);
        scanf(" %c", &symbols[i]);
    }

    memset(nfa, 0, sizeof(nfa));

    printf("\nEnter NFA transitions:\n");
    for (int i = 0; i < n_states; i++)
    {
        for (int j = 0; j < n_symbols; j++)
        {
            int count, state;
            printf("From q%d on '%c', number of transitions: ", i, symbols[j]);
            scanf("%d", &count);
            for (int k = 0; k < count; k++)
            {
                printf("  Enter destination state: ");
                scanf("%d", &state);
                nfa[i * n_symbols + j][state] = 1;
            }
        }
    }

    memset(dfa_states, 0, sizeof(dfa_states));
    dfa_states[0][0] = 1;
    dfa_state_count = 1;

    computeDFA();
    printDFA();

    return 0;
}
