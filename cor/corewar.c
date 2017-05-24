
#include "corewar.h"

void	get_octal_coding(t_data *data, t_carr *carr, int i)
{
	carr->t_ind++;
	if (g_op_tab[i].octal_coding)
		parse_octal(data, carr, g_op_tab[i].label_size);
	else
		parse_non_octal(data, carr, g_op_tab[i].label_size);
}

int		get_opcode(t_data *data, t_carr *carr, int i)
{
	if ((unsigned int)data->map[carr->index].cell == g_op_tab[i].opcode)
	{
		carr->op.opcode = g_op_tab[i].opcode;
		carr->op.name = g_op_tab[i].name;
		get_octal_coding(data, carr, i);

		get_wait_cycle(carr);

		return (TRUE);
	}
	return (FALSE);
}

void	read_cell(t_data *data, t_carr *carr)
{
	int			i;

	i = 0;
	while (get_opcode(data, carr, i) != TRUE && i < OP_COUNT - 2)
		i++;
}

void	clear_op(t_carr *carr)
{
	carr->binary = NULL;
	carr->t_ind = 0;
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

void	move_carriage(t_data *data, t_carr *current)
{
	data->map[current->index].carriage = 0;
	if (current->index >= MEM_SIZE)
		current->index = -1;
	current->index++;
	data->map[current->index].carriage = 1;
}

void	wait_carriage(t_data *data, t_carr *current)
{
	current->op.cycles--;
	if (current->op.cycles == 0)
	{
		manage_function(data, current);
		data->map[current->index].carriage = 0;
		current->index = current->index + current->t_ind;
		if (current->index >= MEM_SIZE)
			current->index = current->index - MEM_SIZE;
		data->map[current->index].carriage = 1;
	}
}

void	manage_corewar(t_data *data)
{
	int		n;
	t_carr *current;

	n = -1;
	while (++n < data->count)
	{
		current = data->champs[n].carriage;
		while (current != NULL)
		{
			if (current->op.cycles == 0)
			{
				clear_op(current);
				read_cell(data, current);
				if (current->op.cycles == 0)
					move_carriage(data, current);
			}
			else
				wait_carriage(data, current);

			current = current->next;
		}
	}
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
		ft_printf("Use -n flag\n");

		int i = 0;
		while (1)
		{
			manage_corewar(data);
			ft_printf("Cycle : %i\n", data->print.cycle);
			sleep(1);
			data->print.cycle++;
			i++;
		}
	}
}

//01110000