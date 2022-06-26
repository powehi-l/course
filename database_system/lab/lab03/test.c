#include <stdio.h>

int main()
{
    int x;
    while ((x = getchar()) != EOF)
        printf("%d", x);
}