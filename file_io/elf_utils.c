#include "main.h"

/**
 * print_magic - Print ELF magic numbers
 * @e_ident: ELF identification array
 */
void print_magic(unsigned char *e_ident)
{
	int i;

	printf("  Magic:   ");
	for (i = 0; i < EI_NIDENT; i++)
	{
		printf("%02x", e_ident[i]);
		if (i < EI_NIDENT - 1)
			printf(" ");
	}
	printf("\n");
}

/**
 * print_class - Print ELF class
 * @e_ident: ELF identification array
 */
void print_class(unsigned char *e_ident)
{
	printf("  Class:                             ");
	if (e_ident[EI_CLASS] == ELFCLASSNONE)
		printf("Invalid class\n");
	else if (e_ident[EI_CLASS] == ELFCLASS32)
		printf("ELF32\n");
	else if (e_ident[EI_CLASS] == ELFCLASS64)
		printf("ELF64\n");
	else
		printf("<unknown: %x>\n", e_ident[EI_CLASS]);
}

/**
 * print_data - Print ELF data encoding
 * @e_ident: ELF identification array
 */
void print_data(unsigned char *e_ident)
{
	printf("  Data:                              ");
	if (e_ident[EI_DATA] == ELFDATANONE)
		printf("Unknown data format\n");
	else if (e_ident[EI_DATA] == ELFDATA2LSB)
		printf("2's complement, little endian\n");
	else if (e_ident[EI_DATA] == ELFDATA2MSB)
		printf("2's complement, big endian\n");
	else
		printf("<unknown: %x>\n", e_ident[EI_DATA]);
}

/**
 * print_header_info - Print ELF header info
 * @h: Pointer to ELF header
 */
void print_header_info(Elf64_Ehdr *h)
{
	printf("  Version:                           %d (current)\n",
	       h->e_ident[EI_VERSION]);

	printf("  OS/ABI:                            ");
	if (h->e_ident[EI_OSABI] == ELFOSABI_SYSV)
		printf("UNIX - System V\n");
	else if (h->e_ident[EI_OSABI] == ELFOSABI_NETBSD)
		printf("UNIX - NetBSD\n");
	else if (h->e_ident[EI_OSABI] == ELFOSABI_SOLARIS)
		printf("UNIX - Solaris\n");
	else
		printf("<unknown: %x>\n", h->e_ident[EI_OSABI]);

	printf("  ABI Version:                       %d\n",
	       h->e_ident[EI_ABIVERSION]);

	printf("  Type:                              ");
	if (h->e_type == ET_NONE)
		printf("NONE (None)\n");
	else if (h->e_type == ET_REL)
		printf("REL (Relocatable file)\n");
	else if (h->e_type == ET_EXEC)
		printf("EXEC (Executable file)\n");
	else if (h->e_type == ET_DYN)
		printf("DYN (Shared object file)\n");
	else if (h->e_type == ET_CORE)
		printf("CORE (Core file)\n");
	else
		printf("<unknown: %x>\n", h->e_type);

	printf("  Entry point address:               0x%lx\n",
	       (unsigned long) h->e_entry);
}
