/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_get_position.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 16:06:42 by astepano          #+#    #+#             */
/*   Updated: 2017/06/02 16:06:47 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

int		asm_get_line(int index, char *file)
{
	int i;
	int	line;

	i = 0;
	line = 0;
	while (file[i] && i < index)
	{
		if (file[i] == '\n')
			line++;
		i++;
	}
	return (line);
}

int		asm_get_place(int index, char *file)
{
	int i;
	int	place;

	i = 0;
	place = 1;
	while (file[i] && i < index)
	{
		if (file[i] == '\n')
			place = 0;
		place++;
		i++;
	}
	return (place);
}
