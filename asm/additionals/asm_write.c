#include "../asm.h"

void		asm_write(t_file_struct *content, int fd)
{
	int i;

	i = 0;
	while (i < 4)
		write(fd, &content->magic[i++], 1);
	i = (int)ft_strlen(content->prog_name);
	write(fd, content->prog_name, (size_t)i);
	while (i < PROG_NAME_LENGTH + 4)
	{
		write(fd, "\0", 1);
		i++;
	}
	asm_generate_magic_proglen(content, (unsigned int)content->count);
	i = 0;
	while (i < 4)
		write(fd, &content->magic[i++], 1);
	i = (int)ft_strlen(content->comment);
	write(fd, content->comment, (size_t)i);
	while (i < COMMENT_LENGTH + 4)
	{
		write(fd, "\0", 1);
		i++;
	}
	write(fd, content->coding_string, (unsigned)content->count);
}