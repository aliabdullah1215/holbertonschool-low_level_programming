#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * main - copies the content of a file to another file
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: 0 on success, or exit with error code on failure
 */
int main(int argc, char *argv[])
{
    int fd_from, fd_to, read_bytes, write_bytes;
    char buffer[1024];
    mode_t permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;

    /* Check number of arguments */
    if (argc != 3)
    {
        dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
        exit(97);
    }

    /* Open source file for reading */
    fd_from = open(argv[1], O_RDONLY);
    if (fd_from == -1)
    {
        dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
        exit(98);
    }

    /* Open destination file for writing (create if doesn't exist, truncate if exists) */
    fd_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, permissions);
    if (fd_to == -1)
    {
        dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
        close(fd_from);
        exit(99);
    }

    /* Copy content using 1024-byte buffer */
    read_bytes = read(fd_from, buffer, 1024);
    while (read_bytes > 0)
    {
        write_bytes = write(fd_to, buffer, read_bytes);
        if (write_bytes != read_bytes)
        {
            dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
            close(fd_from);
            close(fd_to);
            exit(99);
        }
        read_bytes = read(fd_from, buffer, 1024);
    }

    /* Check if read failed - MUST BE IMMEDIATE CHECK AFTER READ */
    if (read_bytes == -1)
    {
        dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
        close(fd_from);
        close(fd_to);
        exit(98);
    }

    /* Close file descriptors */
    if (close(fd_from) == -1)
    {
        dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_from);
        close(fd_to);
        exit(100);
    }

    if (close(fd_to) == -1)
    {
        dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_to);
        exit(100);
    }

    return (0);
}
