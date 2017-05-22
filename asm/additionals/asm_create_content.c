#include "../asm.h"

t_file_struct	*asm_create_content()
{
	t_file_struct	*content;

	content = (t_file_struct*)malloc(sizeof(t_file_struct));
	content->ops = NULL;
	content->comment = NULL;
	content->prog_name = NULL;
	content->prog_size = 0;
	content->file_name = NULL;
	content->coding_string = NULL;
	return (content);
}