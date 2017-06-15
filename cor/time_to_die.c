/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_to_die.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 17:10:47 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:55:59 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	decrease_cicle_to_die(t_data *data)
{
	if ((data->print.cycle_to_die - CYCLE_DELTA) > 0)
		data->print.cycle_to_die -= CYCLE_DELTA;
	else
		data->print.cycle_to_die = 1;
	data->max_checks = 0;
}

void	check_max_checks(t_data *data)
{
	if (data->max_checks > MAX_CHECKS)
		decrease_cicle_to_die(data);
}

void	time_to_die(t_data *data)
{
	kill_carriage(data);
	data->max_checks++;
	if (data->print.nbr_live > NBR_LIVE)
		decrease_cicle_to_die(data);
	else
		check_max_checks(data);
	data->print.time_to_die = data->print.cycle_to_die;
	data->print.nbr_live = 0;
	if (count_processes(data) == 0)
		print_winner(data);
	print_cycle_to_die(data);
}
