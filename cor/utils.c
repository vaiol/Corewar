/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 17:43:18 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:56:04 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				unsigned_to_int(unsigned nbr)
{
	int x;

	x = (int16_t)nbr;
	return (x);
}

int				char_to_int(unsigned char *str)
{
	int nbr;

	nbr = str[0] << 24;
	nbr += str[1] << 16;
	nbr += str[2] << 8;
	nbr += str[3];
	return (nbr);
}

char			*to_two_base(unsigned char c)
{
	int		i;
	int		j;
	char	*binary;

	binary = ft_strnew(7);
	i = 7;
	j = 0;
	while (i >= 0)
	{
		if (c & (1 << i))
			binary[j] = '1';
		else
			binary[j] = '0';
		--i;
		j++;
	}
	return (binary);
}

unsigned char	*int_to_str(int n)
{
	unsigned char *str;

	str = (unsigned char *)malloc(sizeof(char) * 4);
	str[0] = (unsigned char)((n >> 24) & 0xFF);
	str[1] = (unsigned char)((n >> 16) & 0xFF);
	str[2] = (unsigned char)((n >> 8) & 0xFF);
	str[3] = (unsigned char)(n & 0xFF);
	return (str);
}

int				count_processes(t_data *data)
{
	int		processes;
	t_carr	*current;

	processes = 0;
	current = data->carr;
	while (current != NULL)
	{
		processes++;
		current = current->next;
	}
	return (processes);
}
