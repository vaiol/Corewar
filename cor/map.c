/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 17:41:36 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:55:36 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_map(t_data *data)
{
	int i;
	int x;

	i = 0;
	x = 1;
	while (i < MEM_SIZE)
	{
		if (data->map[i].pn == 5)
			ft_printf("%s%02x ", WHITE, data->map[i].cell);
		if (data->map[i].pn == 1)
			ft_printf("%s%02x ", GREEN, data->map[i].cell);
		if (data->map[i].pn == 2)
			ft_printf("%s%02x ", BLUE, data->map[i].cell);
		if (data->map[i].pn == 3)
			ft_printf("%s%02x ", RED, data->map[i].cell);
		if (data->map[i].pn == 4)
			ft_printf("%s%02x ", CYAN, data->map[i].cell);
		if (x >= 64)
		{
			ft_printf("\n");
			x = 0;
		}
		x++;
		i++;
	}
}

void	fill_map(t_data *data, t_champ *champ)
{
	int				pos;
	unsigned int	i;

	pos = champ->start_pos;
	i = 0;
	while (i < champ->prog_size)
	{
		data->map[i + pos].pn = -champ->nb_set;
		data->map[i + pos].cell = champ->program[i];
		i++;
	}
	data->map[pos].carriage = 1;
}

void	prefill_map(t_data *data)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		data->map[i].pn = 5;
		data->map[i].cell = 0;
		data->map[i].carriage = 0;
		i++;
	}
}
