//
// Created by Ivan Solomakhin on 5/24/17.
//

#include "corewar.h"

int 	unsigned_to_int(unsigned nbr)
{
	int x;

	x = (int16_t)nbr;
	return (x);
}

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

//	ft_printf("get indirect index = %i\n", index);

	if (index > MEM_SIZE)
	{
		ft_printf("INDEX > MEM SIZE INDEX = %i\n", index);
		exit(1);
	}


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
	int pos;
	unsigned char *bytes;

	bytes = int_to_str(nbr);

	index = carr->index + (index % IDX_MOD);

//	ft_printf("index = %i\n", index);

	i = -1;
	while (++i < 4)
	{
		pos = index + i;
		if (pos < 0)
			pos = MEM_SIZE + pos;
		map[pos].cell = bytes[i];
		map[pos].pn = carr->pn;
	}
//	free(bytes);
}

void	get_wait_cycle(t_carr *carr)
{
	int i;

	i = -1;
//	ft_printf("%i | opcode = %i\n", carr->id, carr->op.opcode);

	while (++i < OP_COUNT)
	{
		if (g_op_tab[i].opcode == carr->op.opcode)
		{
			carr->op.cycles = g_op_tab[i].cycles - 1;
			if ((int)carr->op.cycles < 0)
				carr->op.cycles = 0;
//			ft_printf("%i | get %i cycles to wait\n", carr->id, carr->op.cycles);
			return ;
		}
	}
	ft_printf("here %i\n", carr->op.opcode);
	sleep(50);
}

void	function_add_sub(t_data *data, t_carr *carr, int *args, unsigned opcode)
{
//	ft_printf("%i | add_sub r%i r%i r%i\n", carr->id, args[0], args[1], args[2]);
	if (opcode == 4)
		carr->reg[args[2]] = carr->reg[args[0]] + carr->reg[args[1]];
	else
		carr->reg[args[2]] = carr->reg[args[0]] - carr->reg[args[1]];
	print_function(data, carr);
	manage_carry(carr, carr->reg[args[2]]);
}

void	function_ld(t_data *data, t_carr *carr, int *args)
{
//	ft_printf("%i | ld %i r%i\n", carr->id, args[0], args[1]);

	if (carr->arg_type[0] == T_DIR)
		carr->reg[args[1]] = args[0];
	else if (carr->arg_type[0] == T_IND)
	{
		carr->reg[args[1]] =  get_indirect_from_map(data->map, carr->index + args[0]);
//		ft_printf("ld = %i", carr->reg[args[1]]);

	}
	print_function(data, carr);
	manage_carry(carr, carr->reg[args[1]]);
////	ft_printf("%i function ld complited\n", carr->reg[args[1]]);
}

void	function_st(t_data *data, t_carr *carr)
{
//	ft_printf("%i | st r%i %i\n", carr->id, carr->op.args[0], carr->op.args[1]);
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
//		free(bytes);
	}
	else if (carr->arg_type[1] == T_REG)
		carr->reg[carr->op.args[1]] = carr->reg[carr->op.args[0]];

	print_function(data, carr);
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
			argv[i] = get_indirect_from_map(data->map, carr->index + args[i]);
	}
	if (opcode == 6)
		carr->reg[args[2]] = argv[0] & argv[1];
	if (opcode == 7)
		carr->reg[args[2]] = argv[0] | argv[1];
	if (opcode == 8)
		carr->reg[args[2]] = argv[0] ^ argv[1];
	print_function(data, carr);
	manage_carry(carr, carr->reg[args[2]]);
}

void	function_live(t_data *data, t_carr *carr) {
	carr->live++;
	data->print.nbr_live++;

//	ft_printf("live == %i\n", unsigned_to_int(carr->op.args[0]));

	int n;

	n = -1;
//	while (++n < data->count)
//	{
//		if (data->champs[n].nb_set == unsigned_to_int(carr->op.args[0]))
//		{
//			data->champs[n].last_live = data->print.cycle;
//			if (data->fl.v == 0)
//			{
////				ft_printf("A process shows that player %i ", carr->pn);
////				ft_printf("(%s) is alive\n", data->champs[carr->pn - 1].prog_name);
//			}
//
//		}
//
//	}
	while (++n < data->count)
	{
//	if (carr->op.args[0] == -carr->pn)
 		if (data->champs[n].nb == -carr->pn)
		{
			data->champs[carr->pn - 1].last_live = data->print.cycle;
			if (data->fl.v == 0)
			{
//				ft_printf("A process shows that player %i ", carr->pn);
//				ft_printf("(%s) is alive\n", data->champs[carr->pn - 1].prog_name);
			}
	}
}
	print_function(data, carr);
}

void	function_zjmp(t_data *data, t_carr *carr)
{
	if (carr->carry == TRUE)
		carr->t_ind = carr->op.args[0];
	print_function(data, carr);
//	ft_printf("jump from %i to %i\n", carr->index, carr->t_ind);
}


void	function_sti(t_data *data, t_carr *carr, int *args)
{
	int res;
	int argv[2];
	int index;

	if (carr->arg_type[1] == T_REG)
		argv[0] = carr->reg[args[1]];
	else if (carr->arg_type[1] == T_DIR)
		argv[0] = args[1];

	else if (carr->arg_type[1] == T_IND)
	{
		index = carr->index + (args[0] % IDX_MOD);
		argv[0] = get_indirect_from_map(data->map, index);
	}
	if (carr->arg_type[2] == T_REG)
		argv[1] = carr->reg[args[2]];
	else if (carr->arg_type[2] == T_DIR)
		argv[1] = args[2];
	res = argv[0] + argv[1];
	print_function(data, carr);
	place_int_on_map(carr, data->map, carr->reg[args[0]], res);
}

void	function_ldi(t_data *data, t_carr *carr, int *args)
{
	int res;
	int argv[2];

	if (carr->arg_type[0] == T_REG)
		argv[0] = carr->reg[args[0]];
	else if (carr->arg_type[0] == T_DIR)
		argv[0] = args[0];
	else if (carr->arg_type[0] == T_IND)
		argv[0] = get_indirect_from_map(data->map, carr->index + (args[0] % IDX_MOD));

	if (carr->arg_type[1] == T_REG)
		argv[1] = carr->reg[args[1]];
	else if (carr->arg_type[1] == T_DIR)
		argv[1] = args[1];
	res = argv[0] + argv[1];
//	ft_printf(" = %i\n", res);
	res = carr->index + (res % IDX_MOD);
	carr->reg[args[2]] = get_indirect_from_map(data->map, res);

	print_function(data, carr);
}

void	function_lldi(t_data *data, t_carr *carr, int *args)
{
	int res;
	int argv[2];

	if (carr->arg_type[0] == T_REG)
		argv[0] = carr->reg[args[0]];
	else if (carr->arg_type[0] == T_DIR)
		argv[0] = args[0];
	else if (carr->arg_type[0] == T_IND)
		argv[0] = get_indirect_from_map(data->map, carr->index + args[0]);

	if (carr->arg_type[1] == T_REG)
		argv[1] = carr->reg[args[1]];
	else if (carr->arg_type[1] == T_DIR)
		argv[1] = args[1];

	argv[0] = unsigned_to_int(argv[0]);

	res = argv[0] + argv[1];

//	ft_printf("res = %i", argv[0]);

	carr->reg[args[2]] = get_indirect_from_map(data->map, carr->index + res);
	print_function(data, carr);
	manage_carry(carr, carr->reg[args[2]]);
}

t_carr	*function_fork_lfork(t_data *data, t_carr *carr, unsigned opcode)
{
//	ft_printf("%i | fork %i ", carr->id, carr->op.args[0]);
	int index;

	index = 0;
	if (opcode == 12)
		index = (carr->index - carr->t_ind) + (carr->op.args[0] % IDX_MOD);

	if (opcode == 15)
		index = (carr->index - carr->t_ind) + carr->op.args[0];

	if (index > MEM_SIZE)
		index = index % MEM_SIZE;

	print_function(data, carr);
	fork_carriage(data, carr, index);
	return (carr);
}

void	function_aff(t_data *data, t_carr *carr)
{
	if (data->fl.a == 1)
	{
		if (ft_isalnum(carr->op.args[0]))
			ft_printf("Aff: %c\n", carr->op.args[0]);
		else
			ft_printf("Aff: ?\n");;
	}
}

void	manage_function(t_data *data, t_carr *carr)
{
	if (carr->op.opcode == 1)
		function_live(data, carr);
	if (carr->op.opcode == 2)
		function_ld(data, carr, carr->op.args);
	if (carr->op.opcode == 3)
		function_st(data, carr);
	if (carr->op.opcode == 4 || carr->op.opcode == 5)
		function_add_sub(data, carr, carr->op.args, carr->op.opcode);
	if (carr->op.opcode == 6 || carr->op.opcode == 7 || carr->op.opcode == 8)
		function_and_or_xor(data, carr, carr->op.args, carr->op.opcode);
	if (carr->op.opcode == 9)
		function_zjmp(data, carr);
	if (carr->op.opcode == 10)
		function_ldi(data, carr, carr->op.args);
	if (carr->op.opcode == 14)
		function_lldi(data, carr, carr->op.args);
	if (carr->op.opcode == 11)
		function_sti(data, carr, carr->op.args);
//	if (carr->op.opcode == 12 || carr->op.opcode == 15)
//		function_fork_lfork(data, carr, carr->op.opcode);
	if (carr->op.opcode == 16)
		function_aff(data, carr);
}
