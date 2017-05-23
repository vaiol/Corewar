#include "asm.h"

void		asm_generate_byte_code(t_file_struct *content)
{
	int fd;

	fd = open("test", O_WRONLY);
	printf("%d\n", fd);
	if (asm_invalid_content(content))
	{
		asm_get_magic(content, COREWAR_EXEC_MAGIC);
		asm_generate_coding_comand(content);
		asm_write(content, fd);
	}
}