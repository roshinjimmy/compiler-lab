#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODS 20
#define MAX_LEN   100

int n; // number of productions
char productions[MAX_PRODS][MAX_LEN];
char firstSet[26][MAX_LEN];
char followSet[26][MAX_LEN];
int computedFirst[26] = {0}, computedFollow[26] = {0};
char nonTerminals[26];
int ntCount = 0;

// Utility: add symbol to set if not already present
void addToSet(char set[], char c) {
    if (strchr(set, c) == NULL) {
        int len = strlen(set);
        set[len] = c;
        set[len + 1] = '\0';
    }
}

void computeFirst(char c) {
    int idx = c - 'A';
    if (computedFirst[idx]) return;
    computedFirst[idx] = 1;

    for (int i = 0; i < n; i++) {
        if (productions[i][0] == c) {
            char *rhs = productions[i] + 2;
            if (*rhs == '\0') continue;
            if (!isupper(*rhs)) {
                addToSet(firstSet[idx], *rhs);
            } else {
                for (char *p = rhs; *p; p++) {
                    if (isupper(*p)) {
                        computeFirst(*p);
                        for (char *q = firstSet[*p - 'A']; *q; q++) {
                            if (*q != '#') addToSet(firstSet[idx], *q);
                        }
                        if (strchr(firstSet[*p - 'A'], '#') == NULL) break;
                    } else {
                        addToSet(firstSet[idx], *p);
                        break;
                    }
                }
            }
        }
    }
}

void computeFollow(char c) {
    int idx = c - 'A';
    if (computedFollow[idx]) return;
    computedFollow[idx] = 1;

    if (productions[0][0] == c) {
        addToSet(followSet[idx], '$');
    }

    for (int i = 0; i < n; i++) {
        char *rhs = productions[i] + 2;
        for (char *p = rhs; *p; p++) {
            if (*p == c) {
                if (*(p + 1)) {
                    if (!isupper(*(p + 1))) {
                        addToSet(followSet[idx], *(p + 1));
                    } else {
                        for (char *q = firstSet[*(p + 1) - 'A']; *q; q++) {
                            if (*q != '#') addToSet(followSet[idx], *q);
                        }
                        if (strchr(firstSet[*(p + 1) - 'A'], '#')) {
                            computeFollow(productions[i][0]);
                            for (char *q = followSet[productions[i][0] - 'A']; *q; q++)
                                addToSet(followSet[idx], *q);
                        }
                    }
                } else if (productions[i][0] != c) {
                    computeFollow(productions[i][0]);
                    for (char *q = followSet[productions[i][0] - 'A']; *q; q++)
                        addToSet(followSet[idx], *q);
                }
            }
        }
    }
}

int main() {
    printf("Number of productions: ");
    scanf("%d", &n);
    getchar();

    printf("Enter productions (e.g., E=TR):\n");
    for (int i = 0; i < n; i++) {
        fgets(productions[i], MAX_LEN, stdin);
        productions[i][strcspn(productions[i], "\n")] = '\0';
        char lhs = productions[i][0];
        if (!strchr(nonTerminals, lhs)) nonTerminals[ntCount++] = lhs;
    }

    memset(firstSet, 0, sizeof(firstSet));
    memset(followSet, 0, sizeof(followSet));

    for (int i = 0; i < ntCount; i++) {
        computeFirst(nonTerminals[i]);
    }

    for (int i = 0; i < ntCount; i++) {
        computeFollow(nonTerminals[i]);
    }

    printf("\nFIRST sets:\n");
    for (int i = 0; i < ntCount; i++) {
        printf("FIRST(%c) = { ", nonTerminals[i]);
        for (char *p = firstSet[nonTerminals[i] - 'A']; *p; p++)
            printf("%c ", *p);
        printf("}\n");
    }

    printf("\nFOLLOW sets:\n");
    for (int i = 0; i < ntCount; i++) {
        printf("FOLLOW(%c) = { ", nonTerminals[i]);
        for (char *p = followSet[nonTerminals[i] - 'A']; *p; p++)
            printf("%c ", *p);
        printf("}\n");
    }

    return 0;
}
