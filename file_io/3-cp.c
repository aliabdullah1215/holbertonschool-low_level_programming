#include "main.h"
#include <stdio.h>

#define BUF_SIZE 1024

/**
 * print_error - prints formatted error and exits
 * @code: exit code
 * @fmt: format string
 * @arg: argument for format
 */
void print_error(int code, const char *fmt, const char *arg)
{
	dprintf(STDERR_FILENO, fmt, arg);
	exit(code);
}

/**
 * safe_close - safely close fd
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
 * main - copies content of a file to another file
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	int fd_from, fd_to;
	ssize_t rbytes, wbytes;
	char buf[BUF_SIZE];

	if (ac != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	fd_from = open(av[1], O_RDONLY);
	if (fd_from == -1)
		print_error(98, "Error: Can't read from file %s\n", av[1]);

	fd_to = open(av[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		safe_close(fd_from);
		print_error(99, "Error: Can't write to %s\n", av[2]);
	}

	while ((rbytes = read(fd_from, buf, BUF_SIZE)) > 0)
	{
		wbytes = write(fd_to, buf, rbytes);
		if (wbytes == -1 || wbytes != rbytes)
		{
			safe_close(fd_from);
			safe_close(fd_to);
			print_error(99, "Error: Can't write to %s\n", av[2]);
		}
	}

	/* تحقق من فشل read() بعد الحلقة مباشرة */
	if (rbytes == -1)
	{
		safe_close(fd_from);
		safe_close(fd_to);
		print_error(98, "Error: Can't read from file %s\n", av[1]);
	}

	safe_close(fd_from);
	safe_close(fd_to);
	return (0);
}
