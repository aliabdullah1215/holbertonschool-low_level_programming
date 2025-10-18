#include "main.h"
#include <stdio.h>

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
	ssize_t rbytes;
	char buf[1024];

	if (ac != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	fd_from = open(av[1], O_RDONLY);
	if (fd_from == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", av[1]);
		exit(98);
	}

	fd_to = open(av[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", av[2]);
		if (close(fd_from) == -1)
			dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_from);
		exit(99);
	}

	/* اقرأ على دفعات 1024 بايت، وتأكد من كتابة كل البايتات المقروءة */
	while ((rbytes = read(fd_from, buf, 1024)) > 0)
	{
		ssize_t written = 0;

		while (written < rbytes)
		{
			ssize_t w = write(fd_to, buf + written, rbytes - written);

			if (w == -1)
			{
				dprintf(STDERR_FILENO, "Error: Can't write to %s\n", av[2]);
				if (close(fd_from) == -1)
					dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_from);
				if (close(fd_to) == -1)
					dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_to);
				exit(99);
			}
			written += w;
		}
	}
	/* فشل في القراءة */
	if (rbytes == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", av[1]);
		if (close(fd_from) == -1)
			dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_from);
		if (close(fd_to) == -1)
			dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_to);
		exit(98);
	}

	/* إغلاق الملفات مع التحقق من الأخطاء */
	if (close(fd_from) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_from);
		exit(100);
	}
	if (close(fd_to) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_to);
		exit(100);
	}

	return (0);
}
