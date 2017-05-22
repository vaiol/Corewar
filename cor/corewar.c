
#include "corewar.h"

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
			data->map[current->index].carriage = 0;
			if (current->index >= MEM_SIZE)
				current->index = -1;
			current->index++;
			data->map[current->index].carriage = 1;
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
	}
}
