
#include "corewar.h"

void	get_octal_coding(t_data *data, t_carr *carr, int i)
{

	carr->op.count_args = g_op_tab[i].count_args;
//	printf("%i == %i\n", i, g_op_tab->count_args);

	carr->t_ind++;
	if (g_op_tab[i].octal_coding)
		parse_octal(data, carr, g_op_tab[i].label_size);
	else if (g_op_tab[i].octal_coding == 0)
		parse_non_octal(data, carr, g_op_tab[i].label_size);

	if (validate_function(carr, carr->op.opcode) == TRUE)
		carr->valid = TRUE;
}

int		get_opcode(t_data *data, t_carr *carr, int i)
{
	if ((unsigned int)data->map[carr->index].cell == g_op_tab[i].opcode)
	{
		carr->op.opcode = g_op_tab[i].opcode;
		carr->g_int = i;
		carr->op.name = g_op_tab[i].name;
		get_wait_cycle(carr);
		return (TRUE);
	}
	return (FALSE);
}

void	read_cell(t_data *data, t_carr *carr)
{
	int	i;

	i = 0;
	while (get_opcode(data, carr, i) != TRUE && i < OP_COUNT - 2)
		i++;
}

void	move_to_temp(t_data *data, t_carr *current)
{
	data->map[current->index].carriage = 0;
	current->index = current->index + current->t_ind;

//	if (current->index > 0)
//		current->index = current->index % MEM_SIZE;
//	if (current->index < 0)
//		current->index = MEM_SIZE + (current->index % MEM_SIZE);

	if (current->index >= MEM_SIZE)
		current->index = current->index - MEM_SIZE;
	else if (current->index < 0)
		current->index = MEM_SIZE + current->index;
	data->map[current->index].carriage = 1;
	if (current->t_ind)
	{
		if (current->valid == FALSE)
			ft_printf("%i | ", current->id);
		print_movements(data, current);
	}
}

void	move_carriage(t_data *data, t_carr *current)
{
		data->map[current->index].carriage = 0;
		if (current->index >= MEM_SIZE)
			current->index = -1;
		if (current->index < 0)
			current->index = MEM_SIZE - current->index;
		current->index++;
		data->map[current->index].carriage = 1;
}

t_carr	*wait_carriage(t_data *data, t_carr *current)
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
				current = function_fork_lfork(data, current, current->op.opcode);
				return (current);
			}
		}
		else
		{
			if (current->valid == TRUE)
				manage_function(data, current);
		}
		move_to_temp(data, current);
	}
	return (current);
}


void	time_to_die(t_data *data)
{

	int n;
	t_carr *current;

//	ft_printf("%i %i\n", data->print.cycle, data->print.cycle_to_die);

	n = -1;
	while (++n < data->count)
	{
		current = data->champs[n].carriage;
		while (current != NULL)
		{
			if (current->live == 0)
				kill_carriage(data, current);
			current->live = 0;
			current = current->next;
		}
	}
	if (data->print.nbr_live > NBR_LIVE)
		data->print.cycle_to_die -= CYCLE_DELTA;
	data->print.time_to_die = data->print.cycle_to_die;
	print_cycle_to_die(data);

}

void	carriage_cycle(t_data *data, t_carr *carr)
{

//	ft_printf("%i | opcode = %i, index = %i\n", carr->id, carr->op.opcode, carr->index);

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

void	manage_corewar(t_data *data)
{
	int		n;
	t_carr *current;

	if (data->print.time_to_die == 0)
	{
//		ft_printf("time = %i\n", data->print.time_to_die);
		time_to_die(data);
	}

	n = -1;
	while (++n < data->count)
	{
		current = data->champs[n].carriage;
		while (current != NULL)
		{
			carriage_cycle(data, current);
			current = current->next;
		}
	}
	data->print.cycle++;
//	ft_printf("time = %i\n", data->print.time_to_die);
	data->print.time_to_die--;
}

void	corewar_v(t_data *data)
{
	while (TRUE)
	{
		print_cycle(data);
		manage_corewar(data);
		usleep(250);
	}
}

void	corewar(t_data *data)
{
	if (data->fl.flags > 0)
	{
		if (data->fl.n == 1)
			init_ncurses(data, &data->print);
		else if (data->fl.v == 1)
			corewar_v(data);
	}
	else
	{
		//	for testing
//		print_map(data);
//		ft_printf("Use -n flag\n");

		int i = 0;
		while (1)
		{
			ft_printf("Cycle : %i\n", data->print.cycle);
				manage_corewar(data);
			usleep(250);
			i++;
		}
	}
}
