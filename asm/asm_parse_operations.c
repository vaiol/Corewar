#include "asm.h"


t_operation	*create_operation()
{
	t_operation	*op;

	op = (t_operation *)malloc(sizeof(t_operation));
	op->args = NULL;
	op->label = NULL;
	op->name = NULL;
	return (op);
}

int			get_label_name(char *file, int i, t_operation *op)
{
	unsigned	j;

	i = asm_skip_empty_lines(file, i);
	j = 0;
	while (ft_strcchr(LABEL_CHARS, file[i + j]))
		j++;
	if (file[i + j] == LABEL_CHAR)
	{
		op->label = ft_strsub(file, (unsigned)i, j);
		return (i + j + 1);
	}
	else if (file[i + j] == ' ' || file[i + j] == '\t' || file[i + j] == '\v'
			 || file[i + j] == '\f' || file[i + j] == '\r')
	{
		op->name = ft_strsub(file, (unsigned)i, j);
		return (i + j + 1);
	}
	else
		return (-1);
}

int			get_args(char *file, int i, t_operation *op)
{
	char		**args;
	char		*str;
	unsigned	j;
	unsigned	tmp;

	i = asm_skip_spaces(file, i);
	j = 0;
	while (file[i + j] && file[i + j] != '\n')
		j++;
	if (file[i + j] == '\0')
		return (-1);
	str = ft_strsub(file, (unsigned)i, j);
	args = ft_strsplit(str, SEPARATOR_CHAR);
	tmp = j;
	j = 0;
	while (args[j])
	{
		str = args[j];
		args[j] = ft_strtrim(args[j]);
		free(str);
		j++;
	}
	op->args = args;
	return (i + tmp + 1);
}

int			get_operation(char *file, int i, t_operation *op)
{
	if ((i = get_label_name(file, i, op)) < 0)
		return (-1);
	if (op->name == NULL && (i = get_label_name(file, i, op)) < 0)
		return (-1);
	if ((i = get_args(file, i, op)) < 0)
		return (-1);
	return (i);
}

void		print_op(t_operation *op)
{
	ft_printf("%s: %s ->\t", op->label, op->name);
	for (int j = 0; op->args && op->args[j]; j++)
		ft_printf("'%s' ", op->args[j]);
	ft_printf("\n");
}

int			asm_parse_operations(char *file, int i, t_file_struct *content)
{
	t_operation	*op;

	op = create_operation();
	i = get_operation(file, i, op);
	print_op(op);

	op = create_operation();
	i = get_operation(file, i, op);
	print_op(op);
	return (i);
}

