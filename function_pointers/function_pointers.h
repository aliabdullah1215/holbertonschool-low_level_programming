#ifndef FUNCTION_POINTERS_H
#define FUNCTION_POINTERS_H

#include <stddef.h> /* for size_t */

/**
 * print_name - prototype for function that prints a name
 * @name: pointer to string
 * @f: pointer to function that takes a char* and returns void
 */
void print_name(char *name, void (*f)(char *));

/**
 * array_iterator - prototype for function that executes another function
 * on each element of an array
 * @array: pointer to array of integers
 * @size: number of elements in the array
 * @action: pointer to function to apply on each element
 */
void array_iterator(int *array, size_t size, void (*action)(int));

#endif /* FUNCTION_POINTERS_H */
