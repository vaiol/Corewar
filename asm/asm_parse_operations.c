/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 15:16:58 by astepano          #+#    #+#             */
/*   Updated: 2017/05/24 15:17:53 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	add_ops(t_file_struct *content, t_operation *op)
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

static int	get_label_name(char *file, int i, t_operation *op, t_file_struct *c)
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
	c->err_index = i;
	return (-1);
}

static int	get_args(char *file, int i, t_operation *op, t_file_struct *c)
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
	{
		c->err_index = i;
		return (-1);
	}
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

static int	get_operation(char *file, int i, t_operation *op, t_file_struct *c)
{
	if ((i = get_label_name(file, i, op, c)) < 0)
	{
		c->err_msg = "err 1";
		return (-1);
	}
	if (op->name == NULL && (i = get_label_name(file, i, op, c)) < 0)
	{
		c->err_msg = "err 2";
		return (-1);
	}
	if ((i = get_args(file, i, op, c)) < 0)
	{
		c->err_msg = "err 3";
		return (-1);
	}
	return (i);
}

int			asm_parse_operations(char *file, int i, t_file_struct *content)
{
	t_operation	*op;

	while (file[i])
	{
		op = asm_create_operation();
		i = get_operation(file, i, op, content);
		if (i < 0)
			return (-1);
		add_ops(content, op);
		i = asm_skip_empty_lines(file, i);
	}
	return (i);
}
