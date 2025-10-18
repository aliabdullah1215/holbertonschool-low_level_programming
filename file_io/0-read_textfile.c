#include "main.h"

/**
 * read_textfile - reads a text file and prints it to STDOUT
 * @filename: path to file
 * @letters: max number of bytes to read and print
 *
 * Return: number of bytes read and printed, or 0 on failure
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	int fd;
	ssize_t rbytes, wbytes;
	char *buf;

	if (!filename || letters == 0)
		return (0);

	buf = malloc(letters);
	if (!buf)
		return (0);

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free(buf);
		return (0);
	}

	rbytes = read(fd, buf, letters);
	if (rbytes == -1)
	{
		free(buf);
		close(fd);
		return (0);
	}

	wbytes = write(STDOUT_FILENO, buf, rbytes);
	if (wbytes == -1 || wbytes != rbytes)
	{
		free(buf);
		close(fd);
		return (0);
	}

	free(buf);
	close(fd);
	return (wbytes);
}

