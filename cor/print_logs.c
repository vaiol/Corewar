/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_logs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 17:42:24 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:55:49 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_movements(t_data *data, t_carr *carr)
{
	int index;
	int c_index;
	int i;

	if (data->fl.l > 0 && carr->op.opcode != 9)
	{
		c_index = carr->index - carr->t_ind;
		if (c_index < 0)
			c_index = MEM_SIZE + c_index;
		if (carr->valid == 0)
			ft_printf("%i | ", carr->id);
		ft_printf("ADV %i (%0#.4x ", carr->t_ind, c_index);
		ft_printf("-> %0#.4x) ", carr->index);
		i = -1;
		while (++i < carr->t_ind)
		{
			index = carr->index - carr->t_ind + i;
			if (index > MEM_SIZE)
				index = index - MEM_SIZE;
			ft_printf("%02x ", data->map[index].cell);
		}
		ft_printf("\n");
	}
}

void	print_func_data(t_carr *carr)
{
	int arg1;
	int arg2;
	int index;

	if (carr->op.opcode == 12)
	{
		index = (carr->index - carr->t_ind) + (carr->op.args[0] % IDX_MOD);
		ft_printf("(%i)", index);
	}
	else if (carr->op.opcode == 15)
		ft_printf("(%i)", carr->index - carr->t_ind + carr->op.args[0]);
	else if (carr->op.opcode == 11)
	{
		arg1 = carr->op.args[1];
		arg2 = carr->op.args[2];
		if (carr->arg_type[1] == T_REG)
			arg1 = carr->reg[carr->op.args[1]];
		if (carr->arg_type[2] == T_REG)
			arg2 = carr->reg[carr->op.args[2]];
		ft_printf("\n%8c -> store to %i + %i ", '|', arg1, arg2);
		ft_printf("= %i ", arg1 + arg2);
		ft_printf("(with pc and mod ");
		ft_printf("%i) ", carr->index + ((arg1 + arg2) % IDX_MOD));
	}
}

void	print_function(t_data *data, t_carr *carr)
{
	int i;

	if (data->fl.l > 0)
	{
		ft_printf("P%5i | %s ", carr->id, carr->op.name);
		i = -1;
		while (++i < (int)carr->op.count_args)
		{
			if (carr->arg_type[i] == T_REG)
				ft_printf("r");
			ft_printf("%i ", carr->op.args[i]);
		}
		if (carr->op.opcode == 9)
		{
			if (carr->carry == TRUE)
				ft_printf("OK");
			else
				ft_printf("FAILED");
		}
		print_func_data(carr);
		ft_printf("\n");
	}
}

void	print_cycle(t_data *data)
{
	if (data->fl.l > 0)
	{
		if (data->print.cycle > 0)
			ft_printf("It is now cycle : %i\n", data->print.cycle);
	}
}

void	print_cycle_to_die(t_data *data)
{
	if (data->fl.l > 0)
		ft_printf("Cycle to die is now %i\n", data->print.cycle_to_die);
}
