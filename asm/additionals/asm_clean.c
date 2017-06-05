/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 16:04:08 by astepano          #+#    #+#             */
/*   Updated: 2017/06/02 16:04:14 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

void		asm_clean_op(t_operation *op)
{
	int	i;

	i = 0;
	while (op->label && op->label[i])
	{
		free(op->label[i]);
		i++;
	}
	if (op->label)
		free(op->label);
	i = 0;
	while (op->args && op->args[i])
	{
		free(op->args[i]);
		i++;
	}
	if (op->args)
		free(op->args);
	if (op->name)
		free(op->name);
	free(op);
}

void		asm_clean(t_file_struct *content)
{
	int	i;

	if (content)
	{
		if (content->prog_name)
			free(content->prog_name);
		if (content->comment)
			free(content->comment);
		if (content->file_name)
			free(content->file_name);
		if (content->coding_string)
			free(content->coding_string);
		i = 0;
		while (content->ops && content->ops[i])
		{
			asm_clean_op(content->ops[i]);
			i++;
		}
		if (content->ops)
			free(content->ops);
		free(content);
	}
}
