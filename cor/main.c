/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 16:08:45 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:55:24 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	create_data(t_data *data)
{
	data->index = 1;
	data->count = 0;
	data->dump = 0;
	data->nb = 0;
	data->fl.flags = 0;
	data->fl.v = 0;
	data->fl.l = 0;
	data->fl.a = 0;
	data->fl.n = 0;
	data->print.cycle = 0;
	data->print.cycle_to_die = CYCLE_TO_DIE;
	data->print.status = 0;
}

void	order_champs(t_data *data)
{
	int		n;
	int		i;
	t_champ	tmp;

	i = -1;
	while (++i < data->count)
	{
		n = -1;
		while (++n < data->count)
		{
			if (n + 1 < data->count)
			{
				if (data->champs[n].nb_set < data->champs[n + 1].nb_set)
				{
					tmp = data->champs[n];
					data->champs[n] = data->champs[n + 1];
					data->champs[n + 1] = tmp;
				}
			}
		}
	}
}

void	check_champ_nb(t_data *data)
{
	int n;

	n = -1;
	while (++n < data->count)
	{
		if (data->champs[n].nb_set == 0)
			set_default_num(data, n, -1);
	}
	order_champs(data);
}

int		main(int argc, char **argv)
{
	int		n;
	t_data	data;

	if (argc == 1)
		error_handler_usage();
	create_data(&data);
	count_champs(&data, argv);
	check_flags(&data, argc, argv);
	check_champ_nb(&data);
	n = -1;
	while (++n < data.count)
		set_start_pos(&data, &data.champs[n], n);
	init_corewar(&data);
	corewar(&data);
	return (0);
}
