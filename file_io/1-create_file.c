#include "main.h"

/**
 * create_file - creates a file and writes text_content into it
 * @filename: name of the file to create
 * @text_content: string to write to the file (may be NULL)
 *
 * Return: 1 on success, -1 on failure
 */
int create_file(const char *filename, char *text_content)
{
	int fd;
	ssize_t wbytes = 0;
	size_t len = 0;

	if (filename == NULL)
		return (-1);

	if (text_content)
	{
		while (text_content[len])
			len++;
	}

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (-1);

	if (len > 0)
	{
		wbytes = write(fd, text_content, len);
		if (wbytes == -1 || (size_t)wbytes != len)
		{
			close(fd);
			return (-1);
		}
	}

	if (close(fd) == -1)
		return (-1);

	return (1);
}

