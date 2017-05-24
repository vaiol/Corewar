/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_get_label.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 15:33:49 by astepano          #+#    #+#             */
/*   Updated: 2017/05/24 15:33:50 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

static int	get_label_len_between(t_file_struct *content, int i1, int i2)
{
	int	len;

	len = 0;
	while (i1 < i2)
	{
		len += content->ops[i1]->len;
		i1++;
	}
	return (len);
}

int			asm_label_len(t_file_struct *content, char *label, int index)
{
	int	index2;
	int	i;

	index2 = 0;
	i = 0;
	while (content->ops[i])
	{
		if (ft_strequ(label, content->ops[i]->label))
		{
			index2 = i;
			break ;
		}
		i++;
	}
	if (index2 > index)
		return (get_label_len_between(content, index, index2));
	else if (index2 < index)
		return (-get_label_len_between(content, index2, index));
	else
		return (0);
}
