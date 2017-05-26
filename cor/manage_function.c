//
// Created by Ivan Solomakhin on 5/24/17.
//

#include "corewar.h"

void	manage_carry(t_carr *carr, int res)
{
	if (res == 0)
		carr->carry = TRUE;
	else
		carr->carry = FALSE;
}

int 	get_indirect_from_map(t_map *map, int index)
{
	unsigned char	str[4];
	int		nbr;

	str[0] = map[index].cell;
	str[1] = map[index + 1].cell;
	str[2] = map[index + 2].cell;
	str[3] = map[index + 3].cell;
	nbr = char_to_int(str);
	return (nbr);
}

void	place_int_on_map(t_carr *carr, t_map *map, int nbr, int index)
{
	int i;
	unsigned char *bytes;

	bytes = int_to_str(nbr);
	index = carr->index + (index % IDX_MOD);
	i = -1;
	while (++i < 4)
	{
		map[index + i].cell = bytes[i];
		map[index + i].pn = carr->pn;
	}
	free(bytes);
}

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
	manage_carry(carr, carr->reg[args[2]]);
}

void	function_ld(t_data *data, t_carr *carr, int *args)
{
//	unsigned char str[4];

	if (carr->arg_type[0] == T_DIR)
		carr->reg[args[1]] = args[0];
	else if (carr->arg_type[0] == T_IND)
		carr->reg[args[1]] = get_indirect_from_map(data->map, args[0]);
	manage_carry(carr, carr->reg[args[1]]);

	ft_printf("%i function ld complited\n", carr->reg[args[1]]);
}

void	function_st(t_data *data, t_carr *carr)
{
	int				i;
	int				index;
	unsigned char	*bytes;

	if (carr->arg_type[1] == T_IND)
	{
		bytes = int_to_str(carr->reg[carr->op.args[0]]);
		index = carr->index + (carr->op.args[1] % IDX_MOD);
		i = -1;
		while (++i < 4)
		{
			data->map[index + i].cell = bytes[i];
			data->map[index + i].pn = carr->pn;
		}
		free(bytes);
	}
	else if (carr->arg_type[1] == T_REG)
		carr->reg[carr->op.args[1]] = carr->reg[carr->op.args[0]];
}

void	function_and_or_xor(t_data *data, t_carr *carr, int *args, unsigned opcode)
{
	int i;
	int argv[2];

	i = -1;
	while (++i < 2)
	{
		if (carr->arg_type[i] == T_REG)
			argv[i] = carr->reg[args[i]];
		else if (carr->arg_type[i] == T_DIR)
			argv[i] = args[i];
		else if (carr->arg_type[i] == T_IND)
			argv[i] = get_indirect_from_map(data->map, args[i]);
	}
	if (opcode == 6)
		carr->reg[args[2]] = argv[0] & argv[1];
	if (opcode == 7)
		carr->reg[args[2]] = argv[0] | argv[1];
	if (opcode == 8)
		carr->reg[args[2]] = argv[0] ^ argv[1];
	manage_carry(carr, carr->reg[args[2]]);
}

void	function_live(t_carr *carr)
{
	if (carr->op.args[0] == carr->pn)
		carr->cycle = 0;
}

void	function_zjmp(t_carr *carr)
{
	if (carr->carry == TRUE)
	{
		unsigned int x = carr->op.args[0];
		int y = (int16_t) x;
		carr->t_ind = y;
	}
}

void	function_sti(t_data *data, t_carr *carr, int *args)
{
	int res;
	int argv[2];

	if (carr->arg_type[1] == T_REG)
		argv[0] = carr->reg[args[1]];
	else if (carr->arg_type[1] == T_DIR)
		argv[0] = args[1];
	else if (carr->arg_type[1] == T_IND)
		argv[0] = get_indirect_from_map(data->map, args[1]);

	if (carr->arg_type[2] == T_REG)
		argv[1] = carr->reg[args[2]];
	else if (carr->arg_type[2] == T_DIR)
		argv[1] = args[2];

	res = argv[0] + argv[1];
	ft_printf("STI RES = %i\n", res);
	place_int_on_map(carr, data->map, carr->reg[args[0]], res);
}

void	function_ldi_lldi(t_data *data, t_carr *carr, int *args, unsigned opcode)
{
	int res;
	int argv[2];

	if (carr->arg_type[0] == T_REG)
		argv[0] = carr->reg[args[0]];
	else if (carr->arg_type[0] == T_DIR)
		argv[0] = args[0];
	else if (carr->arg_type[0] == T_IND)
		argv[0] = get_indirect_from_map(data->map, args[0]);

	if (carr->arg_type[1] == T_REG)
		argv[1] = carr->reg[args[1]];
	else if (carr->arg_type[1] == T_DIR)
		argv[1] = args[1];
	res = argv[0] + argv[1];
	if (opcode == 10)
	{
		res = carr->index + (res % IDX_MOD);
		carr->reg[args[2]] = get_indirect_from_map(data->map, res);
	}
	if (opcode == 14)
	{
		carr->reg[args[2]] = get_indirect_from_map(data->map, res);
		manage_carry(carr, carr->reg[args[2]]);
	}
}

void	function_fork_lfork(t_data *data, t_carr *carr, unsigned opcode)
{
	int index;

	if (opcode == 12)
		index = carr->index + (carr->op.args[0] % IDX_MOD);
	if (opcode == 15)
		index = carr->index + carr->op.args[0];
	fork_carriage(data, carr, index);
}

void	function_aff()
{
	;
}

void	manage_function(t_data *data, t_carr *carr)
{
	if (carr->op.opcode == 1)
		function_live(carr);
	if (carr->op.opcode == 2)
		function_ld(data, carr, carr->op.args);
	if (carr->op.opcode == 3)
		function_st(data, carr);
	if (carr->op.opcode == 4 || carr->op.opcode == 5)
		function_add_sub(carr, carr->op.args, carr->op.opcode);
	if (carr->op.opcode == 6 || carr->op.opcode == 7 || carr->op.opcode == 8)
		function_and_or_xor(data, carr, carr->op.args, carr->op.opcode);
	if (carr->op.opcode == 9)
		function_zjmp(carr);
	if (carr->op.opcode == 10 || carr->op.opcode == 14)
		function_ldi_lldi(data, carr, carr->op.args, carr->op.opcode);
	if (carr->op.opcode == 11)
		function_sti(data, carr, carr->op.args);
	if (carr->op.opcode == 12 || carr->op.opcode == 15)
		function_fork_lfork(data, carr, carr->op.opcode);
	if (carr->op.opcode == 16)
		function_aff();
}