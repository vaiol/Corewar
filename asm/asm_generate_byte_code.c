#include "asm.h"

void	print_op(t_operation *op)
{
	ft_printf("%s: %s ->\t", op->label, op->name);
	for (int j = 0; op->args && op->args[j]; j++)
		ft_printf("'%s' ", op->args[j]);
	ft_printf("\n");
}

void	asm_generate_byte_code(t_file_struct *content)
{
	if (!content)
		ft_printf("Syntax error!");
	else
	{
		ft_printf("name: '%s'\ncomment: '%s'\n", content->prog_name, content->comment);
		for (int i = 0; content->ops && content->ops[i]; ++i)
			print_op(content->ops[i]);
	}
}