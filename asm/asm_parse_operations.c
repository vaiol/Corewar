#include "asm.h"


t_operation	*create_operation()
{
	t_operation	*op;

	op = (t_operation *)malloc(sizeof(t_operation));
	op->args = NULL;
	op->label = NULL;
	op->name = NULL;
	op->index = -1;
	return (op);
}

void		add_ops(t_file_struct *content, t_operation	*op)
{
	int			i;
	t_operation	**new_ops;

	i = 0;
	while (content->ops && content->ops[i])
		i++;
	new_ops = (t_operation	**)malloc(sizeof(t_operation *) * (i + 2));
	i = 0;
	while (content->ops && content->ops[i])
	{
		new_ops[i] = content->ops[i];
		i++;
	}
	new_ops[i++] = op;
	new_ops[i] = NULL;
	if (content->ops)
		free(content->ops);
	content->ops = new_ops;
}

int			get_label_name(char *file, int i, t_operation *op)
{
	unsigned	j;

	i = asm_skip_empty_lines(file, i);
	j = 0;
	while (ft_strcchr(LABEL_CHARS, file[i + j]))
		j++;
	if (file[i + j] == LABEL_CHAR && j > 0)
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

int			asm_parse_operations(char *file, int i, t_file_struct *content)
{
	t_operation	*op;

	while (1)
	{
		op = create_operation();
		i = get_operation(file, i, op);
		if (i < 0)
			return (-1);
		add_ops(content, op);
		i = asm_skip_empty_lines(file, i);
		if (file[i] == '\0')
			break;
	}
	return (i);
}

