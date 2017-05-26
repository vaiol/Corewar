#include "corewar.h"

void	print_map(t_data *data)
{
	int i;
	int x;

	i = 0;
	x = 1;
	while (i < MEM_SIZE)
	{
		if (data->map[i].pn == 5)
			ft_printf("%s%02x ", BLACK, data->map[i].cell);
		if (data->map[i].pn == 1)
			ft_printf("%s%02x ", GREEN, data->map[i].cell);
		if (data->map[i].pn == 2)
			ft_printf("%s%02x ", BLUE, data->map[i].cell);
		if (data->map[i].pn == 3)
			ft_printf("%s%02x ", RED, data->map[i].cell);
		if (data->map[i].pn == 4)
			ft_printf("%s%02x ", CYAN, data->map[i].cell);

//		ft_printf("%s%02x ", RED, data->map[i].cell);

		if (x >= 64)
		{
			ft_printf("\n");
			x = 0;
		}
		x++;
		i++;
	}
};

void	fill_map(t_data *data, t_champ *champ)
{
	int				pos;
	unsigned int	i;

	pos = champ->start_pos;
	i = 0;
	while (i < champ->prog_size)
	{
		data->map[i + pos].pn = champ->nb;
		data->map[i + pos].cell = champ->program[i];
		i++;
	}
	data->map[pos].carriage = 1;
}

void	prefill_map(t_data *data)
{
	int i;

//	if allocate memory for map
//	data->map = (unsigned char *)malloc(sizeof(unsigned char) * MEM_SIZE);
	i = 0;
	while (i < MEM_SIZE)
	{
		data->map[i].pn = 5;
		data->map[i].cell = 0;
		data->map[i].carriage = 0;
		i++;
	}
}
