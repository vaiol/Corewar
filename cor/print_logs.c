//
// Created by Ivan Solomakhin on 6/6/17.
//

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
		ft_printf("ADV = %i (%0#.4x ", carr->t_ind, c_index);
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
	int arg;

	if (carr->op.opcode == 9)
	{
		if (carr->carry == TRUE)
			ft_printf("OK");
		else
			ft_printf("FAILED");
	}
	else if (carr->op.opcode == 12)
		ft_printf("(%i)", (carr->index - carr->t_ind) + (carr->op.args[0] % IDX_MOD));
	else if (carr->op.opcode == 15)
		ft_printf("(%i)", carr->index - carr->t_ind + carr->op.args[0]);


	else if (carr->op.opcode == 11)
	{
		arg = carr->op.args[2];
		if (carr->arg_type[2] == T_REG)
			arg = carr->reg[carr->op.args[2]];
		ft_printf("\n%8c -> store to %i + %i ", '|', carr->op.args[1], arg);
		ft_printf("= %i ", carr->op.args[1] + arg);
		ft_printf("(with pc and mod %i) ", carr->index + (carr->op.args[1] + arg % IDX_MOD));
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

		print_func_data(carr);
		ft_printf("\n");
	}
}

void 	print_cycle(t_data *data)
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