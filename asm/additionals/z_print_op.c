#include "../asm.h"

void	print_op(t_operation *op)
{
	char	*label;

	if (!op->label)
		label = "";
	else
		label = op->label;
	ft_printf("%8s ",  label);
	ft_printf("%5s  -> ", op->name);
	for (int j = 0; op->args && op->args[j]; j++)
		ft_printf("%-9s", op->args[j]);
	ft_printf("\n");
}