#include "main.h"

/**
 * puts_half - prints half of a string, followed by a new line
 * @str: pointer to the string
 *
 * Return: void
 */
void puts_half(char *str)
{
	int len = 0;
	int start;
	int i;

	/* حساب طول السلسلة */
	while (str[len] != '\0')
	{
		len++;
	}

	/* تحديد بداية النصف الثاني */
	if (len % 2 == 0)
		start = len / 2;
	else
		start = (len + 1) / 2;

	/* طباعة من start للنهاية */
	for (i = start; i < len; i++)
	{
		_putchar(str[i]);
	}
	_putchar('\n');
}
