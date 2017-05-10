#include "../asm.h"

t_file_struct	*asm_create_content()
{
	t_file_struct	*content;

	content = (t_file_struct*)malloc(sizeof(t_file_struct));
	content->comment = NULL;
	content->prog_name = NULL;
	content->magic = COREWAR_EXEC_MAGIC;
	content->prog_size = 0;
	return (content);

}