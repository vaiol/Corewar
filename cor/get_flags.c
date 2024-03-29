/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 17:31:44 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:55:08 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	check_dump(t_data *data, int argc, char **argv)
{
	int i;

	i = -1;
	if (++data->index < argc)
	{
		while (++i < (int)ft_strlen(argv[data->index]))
		{
			if (ft_isdigit(argv[data->index][i]) == 0)
				error_handler_usage();
		}
		data->dump = ft_atoi(argv[data->index]);
	}
	else
		error_handler_usage();
}

void	get_flag(t_data *data, int argc, char **argv)
{
	if (ft_strcmp(argv[data->index], "-dump") == 0)
		check_dump(data, argc, argv);
	else if (ft_strcmp(argv[data->index], "-n") == 0)
		set_player_nbr(data, argc, argv);
	else if (ft_strcmp(argv[data->index], "-v") == 0)
		data->fl.v = 1;
	else if (ft_strcmp(argv[data->index], "-l") == 0)
		data->fl.l = 1;
	else if (ft_strcmp(argv[data->index], "-a") == 0)
		data->fl.a = 1;
	else
		error_handler_usage();
}

void	check_flags(t_data *data, int argc, char **argv)
{
	if (data->index >= argc)
		return ;
	if (argv[data->index][0] == '-')
		get_flag(data, argc, argv);
	else
	{
		data->champs[data->nb].nb_set = 0;
		manage_file(data, argv[data->index], data->nb);
	}
	data->index++;
	check_flags(data, argc, argv);
}
