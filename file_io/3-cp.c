#include "main.h"
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 1024

/**
 * print_error - Print error message to stderr and exit with code
 * @code: Exit code
 * @msg: Error message format
 * @arg: Argument (filename or fd)
 */
void print_error(int code, const char *msg, const char *arg)
{
	dprintf(STDERR_FILENO, msg, arg);
	exit(code);
}

/**
 * safe_close - Close a file descriptor safely
 * @fd: The file descriptor
 */
void safe_close(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * copy_file - Copy content from one file to another
 * @src: Source file name
 * @dest: Destination file name
 */
void copy_file(const char *src, const char *dest)
{
	int fd_from, fd_to;
	ssize_t r, w;
	char buf[BUF_SIZE];

	fd_from = open(src, O_RDONLY);
	if (fd_from == -1)
		print_error(98, "Error: Can't read from file %s\n", src);

	fd_to = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		safe_close(fd_from);
		print_error(99, "Error: Can't write to %s\n", dest);
	}

	while ((r = read(fd_from, buf, BUF_SIZE)) != 0)
	{
		if (r == -1)
		{
			safe_close(fd_from);
			safe_close(fd_to);
			print_error(98, "Error: Can't read from file %s\n", src);
		}

		w = write(fd_to, buf, r);
		if (w == -1 || w != r)
		{
			safe_close(fd_from);
			safe_close(fd_to);
			print_error(99, "Error: Can't write to %s\n", dest);
		}
	}

	safe_close(fd_from);
	safe_close(fd_to);
}

/**
 * main - Entry point for cp program
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	if (ac != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	copy_file(av[1], av[2]);
	return (0);
}
