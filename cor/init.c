/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 17:32:53 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:55:17 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init_map(t_data *data)
{
	int n;


	data->map = (t_map *)malloc(sizeof(t_map) * MEM_SIZE);

	prefill_map(data);
	n = -1;
	while (++n < data->count)
		fill_map(data, &data->champs[n]);
	data->print.time_to_die = CYCLE_TO_DIE;
	data->print.nbr_live = 0;
	data->speed = 100;
	data->max_checks = 0;
	data->car_count = 1;
	data->winner = 0;
}

t_carr	*create_carriage(t_data *data, int n)
{
	int		r;
	t_carr	*carr;

	data->champs[n].last_live = 0;
	data->champs[n].carr_count = 1;
	carr = (t_carr *)malloc(sizeof(t_carr));
	carr->pn = n + 1;
	carr->valid = FALSE;
	carr->id = data->car_count;
	data->car_count++;
	carr->g_int = -1;
	carr->live = 0;
	carr->carry = FALSE;
	carr->index = data->champs[n].start_pos;
	carr->op.cycles = 1;
	carr->op.opcode = 0;
	carr->t_ind = 0;
	carr->reg[1] = data->champs[n].nb_set;
	r = 1;
	while (++r < 17)
		carr->reg[r] = 0;
	carr->next = NULL;
	return (carr);
}

void	init_carriage(t_data *data)
{
	int		n;
	t_carr	*new_carr;

	data->carr = NULL;
	n = -1;
	while (++n < data->count)
	{
		if (data->carr == NULL)
			data->carr = create_carriage(data, n);
		else
		{
			new_carr = create_carriage(data, n);
			new_carr->next = data->carr;
			data->carr = new_carr;
		}
	}
}

void	init_corewar(t_data *data)
{
	init_map(data);
	init_carriage(data);
}
