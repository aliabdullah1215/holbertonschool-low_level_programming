#include "function_pointers.h"

/**
 * print_name - calls a function to print a name
 * @name: the string to be printed
 * @f: pointer to function that takes a char* and returns void
 *
 * Return: Nothing
 */
void print_name(char *name, void (*f)(char *))
{
	if (name != 0 && f != 0)
		f(name);
}
