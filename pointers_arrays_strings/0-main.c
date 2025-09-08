#include "main.h"
#include <stdio.h>

int main(void)
{
    char buffer[10];
    int i;

    _memset(buffer, 'A', 10);

    for (i = 0; i < 10; i++)
        printf("%c", buffer[i]);
    printf("\n");
    return (0);
}
