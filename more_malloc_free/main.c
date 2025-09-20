#include "main.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *c;

    c = malloc_checked(10 * sizeof(char));
    c[0] = 'H';
    c[1] = 'i';
    c[2] = '\0';
    printf("%s\n", c);
    free(c);
    return (0);
}

