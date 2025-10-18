#include "main.h"
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 1024

void print_error(int code, const char *msg, const char *arg)
{
	dprintf(STDERR_FILENO, msg, arg);
	exit(code);
}

void safe_close(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

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
		print_error(98, "Error: Can't read from file %s\n", av[1]);

	fd_to = open(av[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		safe_close(fd_from);
		print_error(99, "Error: Can't write to %s\n", av[2]);
	}

	while (1)
	{
		r = read(fd_from, buf, BUF_SIZE);

		/* إذا فشلت القراءة فوراً، اخرج بكود 98 ولا تكتب شيئاً */
		if (r == -1)
		{
			safe_close(fd_from);
			safe_close(fd_to);
			print_error(98, "Error: Can't read from file %s\n", av[1]);
		}
		/* انتهاء الملف */
		if (r == 0)
			break;

		w = write(fd_to, buf, r);
		if (w == -1 || w != r)
		{
			safe_close(fd_from);
			safe_close(fd_to);
			print_error(99, "Error: Can't write to %s\n", av[2]);
		}
	}

	safe_close(fd_from);
	safe_close(fd_to);
	return (0);
}

