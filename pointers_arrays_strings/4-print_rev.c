#include "main.h"

/**
 * print_rev - prints a string in reverse, followed by a new line
 * @s: pointer to the string
 *
 * Return: void
 */
void print_rev(char *s)
{
	int len = 0;

	/* أولاً نحسب الطول */
	while (s[len] != '\0')
	{
		len++;
	}

	/* نطبع من آخر حرف لأول حرف */
	while (len > 0)
	{
		_putchar(s[len - 1]);
		len--;
	}
	_putchar('\n');
}
