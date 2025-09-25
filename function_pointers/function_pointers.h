#ifndef FUNCTION_POINTERS_H
#define FUNCTION_POINTERS_H

/**
 * print_name - prototype for function that prints a name
 * @name: pointer to string
 * @f: pointer to function that takes a char* and returns void
 */
void print_name(char *name, void (*f)(char *));

#endif /* FUNCTION_POINTERS_H */
