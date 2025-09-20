#include "dog.h"
#include <stdlib.h>

/**
 * init_dog - initializes a variable of type struct dog
 * @d: pointer to struct dog
 * @name: dog's name
 * @age: dog's age
 * @owner: dog's owner
 *
 * Description: This function sets the members of struct dog
 * to the values provided by the caller.
 */
void init_dog(struct dog *d, char *name, float age, char *owner)
{
	if (d != NULL)
	{
		d->name = name;
		d->age = age;
		d->owner = owner;
	}
}
