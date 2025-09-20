#ifndef DOG_H
#define DOG_H

/**
 * struct dog - information about a dog
 * @name: dog's name (string)
 * @age: dog's age (float)
 * @owner: dog's owner (string)
 *
 * Description: Defines a dog with a name, age, and owner.
 */
struct dog
{
	char *name;
	float age;
	char *owner;
};

#endif /* DOG_H */
