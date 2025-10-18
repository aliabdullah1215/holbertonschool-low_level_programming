#include "main.h"
#include <stdio.h>

#define BUF_SIZE 1024

/**
 * error_exit - print message to stderr and exit
 * @code: exit code
 * @fmt: format string
 * @arg: argument for format
 */
void error_exit(int code, const char *fmt, const char *arg)
{
	dprintf(STDERR_FILENO, fmt, arg);
	exit(code);
}

/**
 * safe_close - close fd safely
 * @fd: file descriptor
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
 * main - copy content of a file to another
 * @ac: argument count
 * @av: argument values
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	int fd_from, fd_to;
	ssize_t r, w;
	char buf[BUF_SIZE];

	if (ac != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	fd_from = open(av[1], O_RDONLY);
	if (fd_from == -1)
		error_exit(98, "Error: Can't read from file %s\n", av[1]);

	fd_to = open(av[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		safe_close(fd_from);
		error_exit(99, "Error: Can't write to %s\n", av[2]);
	}

	/* loop until EOF or read failure */
	while ((r = read(fd_from, buf, BUF_SIZE)) != 0)
	{
		if (r == -1)
		{
			/* read failed → 98 */
			safe_close(fd_from);
			safe_close(fd_to);
			error_exit(98, "Error: Can't read from file %s\n", av[1]);
		}

		w = write(fd_to, buf, r);
		if (w == -1 || w != r)
		{
			/* write failed → 99 */
			safe_close(fd_from);
			safe_close(fd_to);
			error_exit(99, "Error: Can't write to %s\n", av[2]);
		}
	}

	safe_close(fd_from);
	safe_close(fd_to);
	return (0);
}
