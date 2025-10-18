#include "main.h"
#include <stdio.h>

/**
 * error_exit - prints an error message and exits with a given code
 * @code: exit status
 * @msg: message to print
 * @arg: filename or fd
 */
void error_exit(int code, const char *msg, const char *arg)
{
	dprintf(STDERR_FILENO, msg, arg);
	exit(code);
}

/**
 * main - copies the content of a file to another file
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	int fd_from, fd_to;
	ssize_t rbytes, wbytes;
	char buf[1024];

	if (ac != 3)
		error_exit(97, "Usage: cp %s %s\n", "file_from file_to");

	fd_from = open(av[1], O_RDONLY);
	if (fd_from == -1)
		error_exit(98, "Error: Can't read from file %s\n", av[1]);

	fd_to = open(av[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		close(fd_from);
		error_exit(99, "Error: Can't write to %s\n", av[2]);
	}

	while ((rbytes = read(fd_from, buf, 1024)) > 0)
	{
		wbytes = write(fd_to, buf, rbytes);
		if (wbytes != rbytes)
		{
			close(fd_from);
			close(fd_to);
			error_exit(99, "Error: Can't write to %s\n", av[2]);
		}
	}
	if (rbytes == -1)
		error_exit(98, "Error: Can't read from file %s\n", av[1]);

	if (close(fd_from) == -1)
		error_exit(100, "Error: Can't close fd %d\n", av[1]);
	if (close(fd_to) == -1)
		error_exit(100, "Error: Can't close fd %d\n", av[2]);

	return (0);
}
