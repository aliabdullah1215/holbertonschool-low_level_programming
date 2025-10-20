# C - Hash tables

## Description
This project is part of the Holberton School low-level programming curriculum.  
It focuses on understanding and implementing the **Hash Table** data structure in C.

A **hash table** is a data structure that allows very fast insertion, deletion, and lookup operations.  
It uses a **hash function** to map keys to indices in an array, making data retrieval efficient.

---

## Learning Objectives
At the end of this project, you should be able to explain the following concepts without using Google:

- What is a hash function  
- What makes a good hash function  
- What is a hash table, and how does it work  
- How to handle collisions in a hash table  
- Advantages and drawbacks of using hash tables  
- Common use cases of hash tables  

---

## Requirements
- All code will be compiled on **Ubuntu 20.04 LTS** using `gcc` with flags:  
  `-Wall -Werror -Wextra -pedantic -std=gnu89`
- Allowed editors: `vi`, `vim`, `emacs`
- No use of global variables
- Maximum 5 functions per file
- All functions should be declared in `hash_tables.h`
- Code should follow the **Betty style**
- A `README.md` file is mandatory

---

## Data Structures
```c
/**
 * struct hash_node_s - Node of a hash table
 * @key: The key, string (unique)
 * @value: The value corresponding to a key
 * @next: A pointer to the next node of the list
 */
typedef struct hash_node_s
{
	char *key;
	char *value;
	struct hash_node_s *next;
} hash_node_t;

/**
 * struct hash_table_s - Hash table data structure
 * @size: The size of the array
 * @array: An array of size @size
 */
typedef struct hash_table_s
{
	unsigned long int size;
	hash_node_t **array;
} hash_table_t;
