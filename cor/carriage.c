/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 17:08:14 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:54:29 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	clear_op(t_carr *carr)
{
	carr->binary = NULL;
	carr->t_ind = 0;
	carr->valid = FALSE;
	carr->g_int = -1;
	carr->arg_type[0] = 0;
	carr->arg_type[1] = 0;
	carr->arg_type[2] = 0;
	carr->op.name = NULL;
	carr->op.count_args = 0;
	carr->op.args[0] = 0;
	carr->op.args[1] = 0;
	carr->op.args[2] = 0;
	carr->op.opcode = 0;
	carr->op.cycles = 0;
	carr->op.octal_coding = 0;
	carr->op.label_size = 0;
}

void	headshot(t_data *data)
{
	t_carr	*tmp;

	while (data->carr && data->carr->live == 0)
	{
		tmp = data->carr;
		data->carr = data->carr->next;
		free(tmp);
	}
}

void	kill_carriage(t_data *data)
{
	t_carr	*current;
	t_carr	*prev;
	t_carr	*tmp;

	headshot(data);
	if (data->carr == NULL)
		return ;
	prev = data->carr;
	prev->live = 0;
	current = data->carr->next;
	while (current != NULL)
	{
		if (current->live == 0)
		{
			tmp = current;
			prev->next = current->next;
			current = prev;
			free(tmp);
		}
		prev = current;
		current->live = 0;
		current = current->next;
	}
}

void	fork_carriage(t_data *data, t_carr *carr, int index)
{
	int		r;
	t_carr	*new_carr;
	t_carr	*old_head;

	data->champs[carr->pn - 1].carr_count++;
	new_carr = (t_carr *)malloc(sizeof(t_carr));
	new_carr->id = data->car_count;
	data->car_count++;
	new_carr->pn = carr->pn;
	new_carr->index = index;
	new_carr->live = carr->live;
	new_carr->carry = carr->carry;
	r = 0;
	while (++r < 17)
		new_carr->reg[r] = carr->reg[r];
	clear_op(new_carr);
	old_head = data->carr;
	new_carr->next = old_head;
	data->carr = new_carr;
	if (!data->carr)
		error_handler("No new carr");
}
