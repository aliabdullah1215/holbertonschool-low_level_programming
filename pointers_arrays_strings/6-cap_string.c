#include "main.h"

/**
 * cap_string - capitalizes all words of a string
 * @str: string to modify
 *
 * Return: pointer to the modified string
 */
char *cap_string(char *str)
{
	int i = 0, j;
	char sep[] = " \t\n,;.!?\"(){}";

	/* لو أول حرف في السطر حرف صغير → حوله */
	if (str[0] >= 'a' && str[0] <= 'z')
		str[0] -= 32;

	while (str[i] != '\0')
	{
		for (j = 0; sep[j] != '\0'; j++)
		{
			if (str[i] == sep[j] && (str[i + 1] >= 'a' && str[i + 1] <= 'z'))
			{
				str[i + 1] -= 32;
			}
		}
		i++;
	}

	return (str);
}
