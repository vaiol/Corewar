/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_compare_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 15:30:35 by astepano          #+#    #+#             */
/*   Updated: 2017/05/24 15:30:37 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

int		asm_compare_str(char *str, char *str2)
{
	int	i;
	int	j;

	i = asm_skip_spaces(str, 0);
	j = 0;
	while (str[i] == str2[j])
	{
		i++;
		j++;
	}
	if (str2[j])
		return (0);
	return (i);
}
