#include <stdio.h>
#include <string.h>

char s[100], in[100];
int t = -1;

struct R
{
    char l, r[10];
} p[10];

int red(int n)
{
    for (int i = 0; i < n; i++)
    {
        int len = strlen(p[i].r);
        if (t + 1 >= len && strncmp(&s[t - len + 1], p[i].r, len) == 0)
        {
            printf("%s\t%s\tREDUCE %s->%c\n", s, in, p[i].r, p[i].l);
            t -= len - 1;
            s[t] = p[i].l;
            s[t + 1] = '\0';
            return 1;
        }
    }
    return 0;
}

int main()
{
    int n;
    printf("Rules: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        char l[10];
        scanf("%s", l);
        p[i].l = l[0];
        strcpy(p[i].r, l + 2);
    }
    printf("Input: ");
    scanf("%s", in);

    printf("\nStack\tInput\tAction\n");
    for (int i = 0; in[i];)
    {
        printf("%s\t%s\tSHIFT %c\n", s, in + i, in[i]);
        s[++t] = in[i++];
        s[t + 1] = '\0';
        while (red(n))
            ;
    }
    printf(t == 0 && s[t] == p[0].l ? "ACCEPTED\n" : "REJECTED\n");
    return 0;
}