#include "corewar.h"



void	create_data(t_data *data)
{
	data->index = 1;
	data->count = 0;
	data->dump = 0;
	data->nb = 0;

	data->fl.flags = 0;
	data->fl.v = 0;
	data->fl.l = 0;
	data->fl.a = 0;
	data->fl.n = 0;

	data->print.cycle = 0;
	data->print.cycle_to_die = CYCLE_TO_DIE;
	data->print.status = 0;

}

void	count_champs(t_data *data, char **argv)
{
	int		i;
	char	**split;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] != '-')
		{
			split = ft_strsplit(argv[i], '.');
			if (ft_arrlen(split) > 1)
			{
				if (ft_strcmp(split[1], "cor") == 0)
					data->count++;
			}
		}
		i++;
	}
	if (data->count > 4)
		error_handler("Error : To much players");
	if (data->count == 0)
		error_handler("Error : No players");
	data->champs = (t_champ *)malloc(sizeof(t_champ) * data->count);
}

void	check_champ_nb(t_data *data)
{
	int	n;
	int i;

	n = -1;
	while (++n < data->count)
	{
		i = -1;
		while (++i < data->count)
		{
			if (i != n)
			{
				ft_printf("%i != %i\n", data->champs[i].nb_set, data->champs[n].nb_set);
				if (data->champs[i].nb_set == data->champs[n].nb_set)
					error_handler("Error : number or players match");
			}
		}
	}
}

int		main(int argc, char **argv)
{
	t_data data;

	if (argc == 1)
		error_handler_usage();

	create_data(&data);
//	look for flags and save them to data->fl + add flag "flags";
	count_champs(&data, argv);
	check_flags(&data, argc, argv);
	check_champ_nb(&data);

//	get_files(&data, argv);

	init_corewar(&data);
	ft_printf("was here\n");
//
	corewar(&data);

	return (0);
}


///corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...