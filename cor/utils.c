#include "corewar.h"

void	count_files(t_data *data, char **argv)
{
	int i;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] != '-')
			data->count++;
		i++;
	}
	if (data->count > 4)
		error_handler("Error : To much players");
}