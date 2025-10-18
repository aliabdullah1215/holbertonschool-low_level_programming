#include "main.h"
#include <stdio.h>

#define BUFFER_SIZE 1024

/**
 * print_error - prints an error message to stderr and exits
 * @code: exit status
 * @msg: format string for error message
 * @arg: argument to insert into the message
 */
void print_error(int code, const char *msg, const char *arg)
{
	dprintf(STDERR_FILENO, msg, arg);
	exit(code);
}

/**
 * close_fd - closes a file descriptor and handles errors
 * @fd: file descriptor
 */
void close_fd(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * copy_file - copies the content of one file to another
 * @file_from: name of source file
 * @file_to: name of destination file
 */
void copy_file(const char *file_from, const char *file_to)
{
	int fd_from, fd_to;
	ssize_t rbytes, wbytes;
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

	while (1)
	{
		rbytes = read(fd_from, buf, BUFFER_SIZE);
		if (rbytes == -1)
		{
			close_fd(fd_from);
			close_fd(fd_to);
			print_error(98, "Error: Can't read from file %s\n", file_from);
		}
		if (rbytes == 0)
			break;

		wbytes = write(fd_to, buf, rbytes);
		if (wbytes == -1 || wbytes != rbytes)
		{
			close_fd(fd_from);
			close_fd(fd_to);
			print_error(99, "Error: Can't write to %s\n", file_to);
		}
	}

	close_fd(fd_from);
	close_fd(fd_to);
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
	if (ac != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	copy_file(av[1], av[2]);
	return (0);
}
