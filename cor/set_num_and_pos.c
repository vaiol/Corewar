/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_num_and_pos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 17:42:33 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:55:54 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		is_number(char *str)
{
	int i;

	i = -1;
	if (str[0] == '-' && str[1])
		i++;
	while (++i < (int)ft_strlen(str))
	{
		if (ft_isdigit(str[i]) == 0)
			return (FALSE);
	}
	return (TRUE);
}

void	set_start_pos(t_data *data, t_champ *champ, int nb)
{
	int x;

	x = MEM_SIZE / data->count;
	champ->start_pos = x * (nb);
}

void	set_default_num(t_data *data, int nb, int number)
{
	int n;

	n = -1;
	while (++n < data->count)
	{
		if (data->champs[n].nb_set == number)
		{
			set_default_num(data, nb, number - 1);
			return ;
		}
	}
	data->champs[nb].nb_set = number;
}

void	set_nbr(t_data *data, int nbr)
{
	int n;

	n = -1;
	while (++n < data->count)
	{
		if (data->champs[n].nb_set == nbr)
			data->champs[n].nb_set = 0;
	}
	data->champs[data->nb].nb_set = nbr;
}

void	set_player_nbr(t_data *data, int argc, char **argv)
{
	if (++data->index < argc)
	{
		if (is_number(argv[data->index]) == TRUE)
		{
			if (ft_atoi(argv[data->index]) > 4
				|| ft_atoi(argv[data->index]) < 0)
				error_handler_usage();
			set_nbr(data, -ft_atoi(argv[data->index]));
			data->index++;
		}
		if (data->index < argc)
			manage_file(data, argv[data->index], data->nb);
		else
			error_handler_usage();
	}
	else
		error_handler_usage();
}
