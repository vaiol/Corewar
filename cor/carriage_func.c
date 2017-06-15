/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 17:14:35 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:54:36 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	move_to_temp(t_data *data, t_carr *current)
{
	data->map[current->index].carriage = 0;
	current->index = current->index + current->t_ind;
	if (current->index > 0)
		current->index = current->index % MEM_SIZE;
	if (current->index < 0)
		current->index = MEM_SIZE + (current->index % MEM_SIZE);
	data->map[current->index].carriage = 1;
	if (current->t_ind)
		print_movements(data, current);
}

void	move_carriage(t_data *data, t_carr *current)
{
	data->map[current->index].carriage = 0;
	if (current->index < 0)
		current->index = (MEM_SIZE - 1) - current->index;
	if (current->index >= MEM_SIZE - 1)
		current->index = -1;
	current->index++;
	data->map[current->index].carriage = 1;
}

void	wait_carriage(t_data *data, t_carr *current)
{
	current->op.cycles--;
	if (current->op.cycles == 0)
	{
		if (current->op.opcode)
			get_octal_coding(data, current, current->g_int);
		if (current->op.opcode == 12 || current->op.opcode == 15)
		{
			move_to_temp(data, current);
			if (current->valid == TRUE)
			{
				function_fork(data, current, current->op.opcode);
				return ;
			}
		}
		else
		{
			if (current->valid == TRUE)
				manage_function(data, current);
		}
		move_to_temp(data, current);
	}
	return ;
}

void	carriage_cycle(t_data *data, t_carr *carr)
{
	if (carr->op.cycles == 0)
	{
		clear_op(carr);
		read_cell(data, carr);
		if (carr->op.cycles == 0)
			move_carriage(data, carr);
	}
	else
		wait_carriage(data, carr);
}
