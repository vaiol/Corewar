/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_label_exist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 15:34:55 by astepano          #+#    #+#             */
/*   Updated: 2017/05/24 15:34:56 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

char		*asm_label_exist(t_file_struct *content, char *label)
{
	char	*err;
	int		i;
	int		j;

	if (label[0] == DIRECT_CHAR)
		label = label + 2;
	else
		label = label + 1;
	err = NULL;
	i = 0;
	while (content->ops && content->ops[i])
	{
		j = 0;
		while (content->ops[i]->label && content->ops[i]->label[j])
		{
			if (ft_strequ(content->ops[i]->label[j], label))
				return (err);
			j++;
		}
		i++;
	}
	err = ft_strjoin("No such label ", label);
	return (err);
}
