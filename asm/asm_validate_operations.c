/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_validate_operations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 15:23:33 by astepano          #+#    #+#             */
/*   Updated: 2017/05/24 15:24:57 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*wrong_arg_type(t_operation *op, int i, int arg, char *arg_str)
{
	int		type;

	if (arg == T_LAB)
	{
		if (arg_str[0] == DIRECT_CHAR)
			arg = T_DIR;
		else
			arg = T_IND;
	}
	type = g_op_tab[op->index].args[i];
	if (arg == T_REG)
	{
		if (type == T_DIR || type == T_IND || type == (T_DIR | T_IND))
			return (asm_invalid_type_message(op, i));
	}
	else if (arg == T_DIR)
	{
		if (type == T_REG || type == T_IND || type == (T_REG | T_IND))
			return (asm_invalid_type_message(op, i));
	}
	else if (arg == T_IND)
	{
		if (type == T_DIR || type == T_REG || type == (T_DIR | T_REG))
			return (asm_invalid_type_message(op, i));
	}
	return (NULL);
}

static void	get_index(t_operation *op)
{
	int	i;

	i = 0;
	while (i < OP_COUNT)
	{
		if (ft_strequ(op->name, g_op_tab[i].name))
		{
			op->index = i;
			break ;
		}
		i++;
	}
}

static char	*validate_count_args(t_operation *op)
{
	char		*err;
	unsigned	count;

	count = 0;
	while (op->args[count])
		count++;
	err = NULL;
	if (count < g_op_tab[op->index].count_args)
		err = ft_strjoin("Invalid parameter count for instruction ", op->name);
	else if (count > g_op_tab[op->index].count_args)
		err = asm_invalid_type_message(op, g_op_tab[op->index].count_args);
	return (err);
}

static char	*validate_args(t_file_struct *content, t_operation *op)
{
	char	*err;
	int		arg;
	int		i;

	err = NULL;
	i = 0;
	while (op->args[i])
	{
		arg = asm_is_arg(op->args[i]);
		if (arg < 0)
			return (asm_invalid_type_message(op, i));
		if (arg == T_LAB && (err = asm_label_exist(content, op->args[i])))
			return (err);
		if ((err = wrong_arg_type(op, i, arg, op->args[i])))
			return (err);
		i++;
	}
	return (err);
}

char		*asm_validate_operations(t_file_struct *content)
{
	char	*error;
	int		i;

	i = 0;
	while (content->ops[i])
	{
		get_index(content->ops[i]);
		if (content->ops[i]->index == -1)
			return (ft_strjoin("Invalid instruction ", content->ops[i]->name));
		if ((error = validate_count_args(content->ops[i])))
			return (error);
		if ((error = validate_args(content, content->ops[i])))
			return (error);
		i++;
	}
	return (NULL);
}
