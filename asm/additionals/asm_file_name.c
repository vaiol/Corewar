/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_file_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 15:32:39 by astepano          #+#    #+#             */
/*   Updated: 2017/05/24 15:32:44 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

char	*asm_file_name(char *str, char *file_name)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (file_name[i])
	{
		if (file_name[i] == '.')
			j = i;
		i++;
	}
	str = ft_strsub(file_name, 0, j);
	str = ft_strfjoin(str, ".cor", FIRST);
	return (str);
}
