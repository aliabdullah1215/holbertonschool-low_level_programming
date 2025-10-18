#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

/* _putchar function */
int _putchar(char c);

/* Task 0: Read text file */
ssize_t read_textfile(const char *filename, size_t letters);

/* Task 1: Create a file */
int create_file(const char *filename, char *text_content);

/* Task 2: Append text to a file */
int append_text_to_file(const char *filename, char *text_content);

#endif
