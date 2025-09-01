#include "main.h"

/**
 * _strncat - concatenates two strings, using at most n bytes from src
 * @dest: destination string
 * @src: source string
 * @n: maximum number of bytes from src
 *
 * Return: pointer to dest
 */
char *_strncat(char *dest, char *src, int n)
{
	int i = 0;
	int j = 0;

	/* إيجاد نهاية dest */
	while (dest[i] != '\0')
	{
		i++;
	}

	/* نسخ src (بحد أقصى n) */
	while (j < n && src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	/* إضافة null byte */
	dest[i] = '\0';

	return (dest);
}
