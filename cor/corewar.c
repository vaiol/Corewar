
#include "corewar.h"

void	get_octal_coding(t_data *data, t_carr *carr, int i)
{
	carr->op.count_args = g_op_tab[i].count_args;
	carr->t_ind++;
	if (g_op_tab[i].octal_coding)
		parse_octal(data, carr, g_op_tab[i].label_size);
	else if (g_op_tab[i].octal_coding == 0)
		parse_non_octal(data, carr, g_op_tab[i].label_size);
}


int		get_opcode(t_data *data, t_carr *carr, int i)
{
	if ((unsigned int)data->map[carr->index].cell == g_op_tab[i].opcode)
	{

//		ft_printf("hjk");
//		sleep(9);
//
		carr->op.opcode = g_op_tab[i].opcode;
		carr->op.name = g_op_tab[i].name;


		get_octal_coding(data, carr, i);


//		carr->op.opcode = g_op_tab[i].opcode;

//		ft_printf("%i | to validate with opcode %i where original opcode = %i, carr index = %i, map = %x\n", carr->id, carr->op.opcode, g_op_tab[i].opcode, carr->index, data->map[carr->index].cell);

		if (validate_function(carr, carr->op.opcode) == TRUE)
		{
			carr->valid = TRUE;
		}
//		ft_printf("%i | to get_wait_cycle\n", carr->id);


		get_wait_cycle(carr);
		return (TRUE);
	}
	return (FALSE);
}

//int		get_opcode(t_data *data, t_carr *carr, int i)
//{
//	if ((unsigned int)data->map[carr->index].cell == g_op_tab[i].opcode)
//	{
//		carr->op.opcode = g_op_tab[i].opcode;
//		carr->op.name = g_op_tab[i].name;
//		get_octal_coding(data, carr, i);
//		if (validate_function(carr, carr->op.opcode) == TRUE)
//			get_wait_cycle(carr);
//		else
//		{
//			ft_printf("WAS HERE, t_ind = %i\n", carr->t_ind);
//			move_to_temp(data, carr);
//			clear_op(carr);
//		}
//		return (TRUE);
//	}
//	return (FALSE);
//}

void	read_cell(t_data *data, t_carr *carr)
{
	int	i;

	i = 0;
	while (get_opcode(data, carr, i) != TRUE && i < OP_COUNT - 2)
		i++;
}

void	move_to_temp(t_data *data, t_carr *current)
{
	if (current->t_ind)
	{
		ft_printf("ADV = %i (%0#.4x ", current->t_ind, current->index);
	}
	data->map[current->index].carriage = 0;
	current->index = current->index + current->t_ind;
	if (current->index >= MEM_SIZE)
		current->index = current->index - MEM_SIZE;
	else if (current->index < 0)
		current->index = MEM_SIZE + current->index;
	data->map[current->index].carriage = 1;

	ft_printf("=> %0#.4x)(to %i) & valid = %i carriage id = %i\n", current->index, current->index, current->valid, current->id);

//	current->t_ind = 0;
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

	ft_printf("time to die, cycle to die now %i\n", data->print.cycle_to_die);

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
	carr = carr->next;
}

void	manage_corewar(t_data *data)
{
	int		n;
	t_carr *current;

	if (data->print.time_to_die == 0)
		time_to_die(data);
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
	data->print.time_to_die--;
}

void	corewar(t_data *data)
{
	if (data->fl.flags > 0)
	{
		if (data->fl.n == 1)
		{
			init_ncurses(data, &data->print);
			nc_pause(data);
		}
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
			usleep(0);
			i++;
		}
	}
}
