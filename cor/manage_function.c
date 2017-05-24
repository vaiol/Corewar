//
// Created by Ivan Solomakhin on 5/24/17.
//

#include "corewar.h"

void	get_wait_cycle(t_carr *carr)
{
	if (carr->op.opcode == 16)
		carr->op.cycles = 2;
	if (carr->op.opcode == 2 || carr->op.opcode == 3)
		carr->op.cycles = 5;
	if (carr->op.opcode == 6 || carr->op.opcode == 7 || carr->op.opcode == 8)
		carr->op.cycles = 6;
	if (carr->op.opcode == 1 || carr->op.opcode == 4 ||
		carr->op.opcode == 5 || carr->op.opcode == 13)
		carr->op.cycles = 10;
	if (carr->op.opcode == 9)
		carr->op.cycles = 20;
	if (carr->op.opcode == 10 || carr->op.opcode == 11)
		carr->op.cycles = 25;
	if (carr->op.opcode == 14)
		carr->op.cycles = 50;
	if (carr->op.opcode == 12)
		carr->op.cycles = 800;
	if (carr->op.opcode == 15)
		carr->op.cycles = 1000;
}

void	function_add_sub(t_carr *carr, int *args, unsigned opcode)
{
	if (opcode == 4)
	{
		carr->reg[args[2]] = carr->reg[args[0]] + carr->reg[args[1]];
		ft_printf("function add complited\n");
	}
	else
	{
		carr->reg[args[2]] = carr->reg[args[0]] - carr->reg[args[1]];
		ft_printf("function sub complited\n");
	}
}

void	function_ld(t_carr *carr, int *args)
{
	carr->reg[args[1]] = carr->reg[args[0]];

	ft_printf("%i function ld complited\n", carr->reg[args[0]]);
}

void	function_st(t_data *data, t_carr *carr)
{
	int				index;
	unsigned char	bytes[4];

	int n = carr->reg[carr->op.args[0]];

	bytes[0] = (n >> 24) & 0xFF;
	bytes[1] = (n >> 16) & 0xFF;
	bytes[2] = (n >> 8) & 0xFF;
	bytes[3] = n & 0xFF;

//	if (carr->arg_type[0] == T_REG)

	index = carr->index + (carr->op.args[1] % IDX_MOD);
	ft_printf("ST Index = %i N = %i\n", index , n);

	int i;

	i = 0;

	while (i < 4)
	{
		data->map[index + i].cell = bytes[i];
		data->map[index + i].pn = carr->pn;

		i++;
	}


//		data->map[carr->index + carr->op.args[1]] = carr->reg[carr->op.args[0]];
}

void	manage_function(t_data *data, t_carr *carr)
{
	int c = data->index;
	c++;
//	if (carr->op.opcode == 1)
//		function_live(data, carr);
	if (carr->op.opcode == 2)
		function_ld(carr, carr->op.args);
	if (carr->op.opcode == 3)
		function_st(data, carr);
	if (carr->op.opcode == 4 || carr->op.opcode == 5)
		function_add_sub(carr, carr->op.args, carr->op.opcode);
}