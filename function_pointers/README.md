# 0x0F. C - Function pointers

## Description
This project is part of the Holberton School curriculum.  
It introduces **function pointers** in C: how to declare them, how to use them, and why they are powerful.  
You will learn how function pointers can be passed as arguments to functions, and how they can be used to call different functions dynamically.

## Learning Objectives
By the end of this project, you should be able to explain:
- What are function pointers and how to use them
- What does a function pointer exactly hold
- Where does a function pointer point to in the virtual memory

## Requirements
- Allowed editors: `vi`, `vim`, `emacs`
- All your files will be compiled on Ubuntu 20.04 LTS using `gcc`, with options:  
  `-Wall -Werror -Wextra -pedantic -std=gnu89`
- All your files should end with a new line
- A `README.md` file at the root of the project folder is mandatory
- Your code should follow the **Betty style**
- No global variables allowed
- Maximum 5 functions per file
- Allowed standard library functions: `malloc`, `free`, and `exit`
- You are allowed to use `_putchar`
- You don’t need to push `_putchar.c` (we will use our own file)
- The prototypes of all your functions should be included in `function_pointers.h`
- All your header files should be include guarded

## Project Structure
- `0-print_name.c`: Function that prints a name using a function pointer.
- `1-array_iterator.c`: Function that executes a function given as a parameter on each element of an array.
- `2-int_index.c`: Function that searches for an integer in an array using a comparison function.
- `3-calc.h`, `3-op_functions.c`, `3-get_op_func.c`, `3-main.c`: Simple calculator program using function pointers.

## Compilation
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 <main_file.c> <task_file.c> -o output
