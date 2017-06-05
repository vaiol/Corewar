/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_get_prog_len.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 15:34:09 by astepano          #+#    #+#             */
/*   Updated: 2017/05/24 15:37:28 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

static void	add_op_len(int op_index, t_file_struct *content)
{
	int j;
	int	arg;

	j = 0;
	while (content->ops[op_index]->args[j])
	{
		arg = asm_is_arg(content->ops[op_index]->args[j]);
		if (arg == T_REG)
			content->ops[op_index]->len++;
		else if ((arg == T_IND)
				|| (arg == T_LAB
					&& content->ops[op_index]->args[j][0] != DIRECT_CHAR))
			content->ops[op_index]->len += 2;
		else if (arg == T_DIR || arg == T_LAB)
		{
			if (!g_op_tab[content->ops[op_index]->index].label_size)
				content->ops[op_index]->len += 2;
			content->ops[op_index]->len += 2;
		}
		j++;
	}
}

void		asm_get_prog_len(t_file_struct *content)
{
	int	i;

	i = 0;
	while (content->ops[i] && !content->ops[i]->eof)
	{
		content->ops[i]->len = 1;
		if (g_op_tab[content->ops[i]->index].octal_coding)
			content->ops[i]->len++;
		add_op_len(i, content);
		i++;
	}
}
