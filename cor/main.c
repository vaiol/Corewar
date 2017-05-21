#include "corewar.h"

void	create_data(t_data *data)
{
	data->index = 1;
	data->count = 0;

	data->fl.flags = 0;
	data->fl.n = 0;

	data->rules.cycle = 0;
	data->rules.cycle_to_die = CYCLE_TO_DIE;
	data->rules.status = 0;

	data->print.cycle = 0;
	data->print.cycle_to_die = CYCLE_TO_DIE;
	data->print.status = 0;

}

int		main(int argc, char **argv)
{
	t_data data;

	create_data(&data);

//	look for flags and save them to data->fl + add flag "flags";
	check_flags(argc, argv, &data);
//	check files for size, min/max number and save them to struct arr data->champs;
	get_files(&data, argv);
//	create and fill map, create first carriage for champion
	init_corewar(&data);

//	game start
	corewar(&data);

	return (0);
}
