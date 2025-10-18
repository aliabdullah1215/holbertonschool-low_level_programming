#include "main.h"

/**
 * print_error - Print error message and exit with code 98
 * @msg: Error message
 */
void print_error(const char *msg)
{
	dprintf(STDERR_FILENO, "%s\n", msg);
	exit(98);
}

/**
 * main - Displays the ELF header of a file
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: 0 on success, 98 on failure
 */
int main(int ac, char **av)
{
	int fd;
	ssize_t n_read;
	Elf64_Ehdr header;

	if (ac != 2)
		print_error("Usage: elf_header elf_filename");

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		print_error("Error: Can't read file");

	n_read = read(fd, &header, sizeof(header));
	if (n_read != sizeof(header))
	{
		close(fd);
		print_error("Error: Can't read ELF header");
	}

	if (header.e_ident[EI_MAG0] != ELFMAG0 ||
	    header.e_ident[EI_MAG1] != ELFMAG1 ||
	    header.e_ident[EI_MAG2] != ELFMAG2 ||
	    header.e_ident[EI_MAG3] != ELFMAG3)
	{
		close(fd);
		print_error("Error: Not an ELF file");
	}

	printf("ELF Header:\n");
	print_magic(header.e_ident);
	print_class(header.e_ident);
	print_data(header.e_ident);
	print_header_info(&header);

	close(fd);
	return (0);
}
