/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 17:54:50 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:54:55 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	manage_corewar(t_data *data)
{
	t_carr *current;

	current = data->carr;
	while (current != NULL)
	{
//		if (current->op.cycles);
		carriage_cycle(data, current);
		current = current->next;
	}
	if (data->print.time_to_die == 0)
		time_to_die(data);
	data->print.cycle++;
	data->print.time_to_die--;
}

void	corewar_l(t_data *data)
{
	while (TRUE)
	{
		print_cycle(data);
		manage_corewar(data);
	}
}

void	corewar(t_data *data)
{
	int i;

	if (data->fl.v == 1 || data->fl.l == 1)
	{
		if (data->fl.v == 1)
			init_ncurses(data, &data->print);
		else if (data->fl.l == 1)
			corewar_l(data);
	}
	else if (data->fl.flags == 0 || (data->fl.a == 1 && data->fl.flags == 1))
	{
		if (data->dump != 0)
		{
			i = -1;
			while (++i < data->dump)
				manage_corewar(data);
			print_map(data);
		}
		else
		{
			while (TRUE)
				manage_corewar(data);
		}
	}
}
