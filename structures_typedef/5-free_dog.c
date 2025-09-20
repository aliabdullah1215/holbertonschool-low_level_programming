#include "dog.h"
#include <stdlib.h>

/**
 * free_dog - frees memory allocated for a dog
 * @d: pointer to dog_t to free
 *
 * Description: Frees the memory allocated for the struct dog,
 * including the name and owner strings.
 */
void free_dog(dog_t *d)
{
	if (d != NULL)
	{
		free(d->name);
		free(d->owner);
		free(d);
	}
}
