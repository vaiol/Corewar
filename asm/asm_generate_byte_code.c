#include "asm.h"

void	asm_generate_byte_code(t_file_struct *content)
{
	if (!content)
		ft_printf("Syntax error!");
	else
	{
		ft_printf("%s\n%s\n", content->prog_name, content->comment);
	}
}