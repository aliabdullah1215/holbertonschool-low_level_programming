#include "main.h"
#include <stdio.h>

#define BUFFER_SIZE 1024

/**
 * print_error - print formatted error to stderr then exit
 * @code: exit status
 * @fmt:  printf-like format string
 * @arg:  single argument inserted into @fmt
 */
static void print_error(int code, const char *fmt, const char *arg)
{
	dprintf(STDERR_FILENO, fmt, arg);
	exit(code);
}

/**
 * close_fd - close fd and handle error
 * @fd: file descriptor
 */
static void close_fd(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * copy_file - copy file_from -> file_to using a 1024B buffer
 * @file_from: source path
 * @file_to: destination path
 */
static void copy_file(const char *file_from, const char *file_to)
{
	int fd_from, fd_to;
	ssize_t rbytes;
	char buf[BUFFER_SIZE];

	fd_from = open(file_from, O_RDONLY);
	if (fd_from == -1)
		print_error(98, "Error: Can't read from file %s\n", file_from);

	fd_to = open(file_to, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		close_fd(fd_from);
		print_error(99, "Error: Can't write to %s\n", file_to);
	}

	for (;;)
	{
		/* 1) اقرأ */
		rbytes = read(fd_from, buf, BUFFER_SIZE);
		if (rbytes == -1)
		{
			/* فشل القراءة → 98 (ولا نحاول أي كتابة) */
			close_fd(fd_from);
			close_fd(fd_to);
			print_error(98, "Error: Can't read from file %s\n", file_from);
		}
		if (rbytes == 0)
			break; /* EOF */

		/* 2) اكتب كل ما قرأته (التعامل مع الكتابة الجزئية) */
		{
			ssize_t written = 0;

			while (written < rbytes)
			{
				ssize_t w = write(fd_to, buf + written, rbytes - written);

				if (w == -1)
				{
					close_fd(fd_from);
					close_fd(fd_to);
					print_error(99, "Error: Can't write to %s\n", file_to);
				}
				written += w;
			}
		}
	}

	close_fd(fd_from);
	close_fd(fd_to);
}

/**
 * main - cp file_from file_to
 * @ac: argc
 * @av: argv
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
