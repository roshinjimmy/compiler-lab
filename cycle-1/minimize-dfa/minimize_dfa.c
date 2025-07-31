#include <stdio.h>
#include <string.h>

#define MAX_STATES 20
#define MAX_SYMBOLS 10

int dfa[MAX_STATES][MAX_SYMBOLS];
int minimizedDFA[MAX_STATES][MAX_SYMBOLS];
int n_states, n_symbols;
int final_states[MAX_STATES], n_final;
char symbols[MAX_SYMBOLS];

int partitions[MAX_STATES], new_partitions[MAX_STATES];
int group[MAX_STATES][MAX_STATES];
int group_size[MAX_STATES];
int num_groups = 0;

int are_distinguishable(int s1, int s2)
{
    for (int i = 0; i < n_symbols; i++)
    {
        int t1 = dfa[s1][i];
        int t2 = dfa[s2][i];
        if (partitions[t1] != partitions[t2])
            return 1;
    }
    return 0;
}

void initialize_partitions()
{
    for (int i = 0; i < n_states; i++)
    {
        partitions[i] = 1;
        for (int j = 0; j < n_final; j++)
        {
            if (i == final_states[j])
            {
                partitions[i] = 0;
                break;
            }
        }
    }
}

void refine_partitions()
{
    int changed;
    int max_group = 1;

    do
    {
        changed = 0;
        for (int i = 0; i < n_states; i++)
            new_partitions[i] = partitions[i];

        for (int g = 0; g <= max_group; g++)
        {

            int states_in_group[MAX_STATES], count = 0;
            for (int i = 0; i < n_states; i++)
            {
                if (partitions[i] == g)
                    states_in_group[count++] = i;
            }

            for (int i = 0; i < count; i++)
            {
                for (int j = i + 1; j < count; j++)
                {
                    int s1 = states_in_group[i];
                    int s2 = states_in_group[j];

                    if (are_distinguishable(s1, s2))
                    {

                        max_group++;
                        new_partitions[s2] = max_group;

                        for (int k = j + 1; k < count; k++)
                        {
                            int s3 = states_in_group[k];
                            if (!are_distinguishable(s2, s3))
                            {
                                new_partitions[s3] = max_group;
                            }
                        }
                        changed = 1;
                        break;
                    }
                }
                if (changed)
                    break;
            }
            if (changed)
                break;
        }

        memcpy(partitions, new_partitions, sizeof(partitions));
    } while (changed);
}

void build_minimized_dfa()
{
    num_groups = 0;
    memset(group_size, 0, sizeof(group_size));

    for (int i = 0; i < MAX_STATES; i++)
        for (int j = 0; j < MAX_STATES; j++)
            group[i][j] = -1;

    for (int i = 0; i < n_states; i++)
    {
        int g = partitions[i];
        int found = -1;
        for (int j = 0; j < num_groups; j++)
        {
            if (group[j][0] != -1 && partitions[group[j][0]] == g)
            {
                group[j][group_size[j]++] = i;
                found = j;
                break;
            }
        }
        if (found == -1)
        {
            group[num_groups][group_size[num_groups]++] = i;
            num_groups++;
        }
    }

    for (int i = 0; i < num_groups; i++)
    {
        int rep = group[i][0];
        for (int j = 0; j < n_symbols; j++)
        {
            int t = dfa[rep][j];
            minimizedDFA[i][j] = -1;
            for (int k = 0; k < num_groups; k++)
            {
                for (int l = 0; l < group_size[k]; l++)
                {
                    if (group[k][l] == t)
                    {
                        minimizedDFA[i][j] = k;
                        break;
                    }
                }
                if (minimizedDFA[i][j] != -1)
                    break;
            }
        }
    }
}

void print_minimized_dfa()
{
    printf("\nMinimized DFA Transition Table:\n");
    for (int i = 0; i < num_groups; i++)
    {
        printf("State %d [", i);
        for (int j = 0; j < group_size[i]; j++)
            printf("q%d ", group[i][j]);
        printf("]:\n");

        for (int j = 0; j < n_symbols; j++)
        {
            printf("  On '%c' -> State %d\n", symbols[j], minimizedDFA[i][j]);
        }
    }
}

int main()
{
    printf("Enter number of states in DFA: ");
    scanf("%d", &n_states);

    printf("Enter number of input symbols: ");
    scanf("%d", &n_symbols);

    printf("Enter input symbols:\n");
    for (int i = 0; i < n_symbols; i++)
    {
        printf("Symbol %d: ", i + 1);
        scanf(" %c", &symbols[i]);
    }

    printf("\nEnter transition table (destination state for each input):\n");
    for (int i = 0; i < n_states; i++)
    {
        for (int j = 0; j < n_symbols; j++)
        {
            printf("From q%d on '%c': ", i, symbols[j]);
            scanf("%d", &dfa[i][j]);
        }
    }

    printf("Enter number of final states: ");
    scanf("%d", &n_final);

    printf("Enter final state numbers: ");
    for (int i = 0; i < n_final; i++)
    {
        scanf("%d", &final_states[i]);
    }

    initialize_partitions();
    refine_partitions();
    build_minimized_dfa();
    print_minimized_dfa();

    return 0;
}
