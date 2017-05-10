#include "corewar.h"

void	create_data(t_data *data)
{
	data->index = 1;

	data->fl.flags = 0;
	data->fl.n = 0;
}

int		main(int argc, char **argv)
{
	t_data data;

	create_data(&data);
	check_flags(argc, argv, &data);
}