#include "corewar.h"

void	create_data(t_data *data)
{
	data->index = 1;
	data->count = 0;

	data->fl.flags = 0;
	data->fl.n = 0;
}


int		main(int argc, char **argv)
{
	t_data data;

	create_data(&data);

//	look for flags and save them to data->fl + add flag "flags";
	check_flags(argc, argv, &data);
//	check files for size, min/max number and save them to struct arr data->champs;
	get_files(&data, argv);


	int i;

	i = 0;


	off_t	size;

	size = lseek(data.champs[0].code, 0, SEEK_END);
//	if (size < 0)
//		error_handler("Error : file is not valid");

	ft_printf("%i\n", size);

//	while (data.champs[0].code[i])
//	{
//		ft_printf("%i", (int)data.champs[0].code[i]);
//		i++;
//	}

//	ft_printf("%s\n", data.champs[0].code);

	return (0);
}