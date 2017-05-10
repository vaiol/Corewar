#include "corewar.h"

void	check_size(int fd, t_data *data, int num)
{
	off_t	size;
	int		real_size;

	size = lseek(fd, 0, SEEK_END);
	if (size < 0)
		error_handler("Error : file is not valid");

	real_size = (size_t)size - PROG_NAME_LENGTH - COMMENT_LENGTH;
	ft_printf("%i\n", real_size);

	if (real_size < 0)
		error_handler("Error : champ is not valid");

	if (real_size > CHAMP_MAX_SIZE)
		error_handler("Error : champion is too large");
	data->champs[num].size = (size_t)size;
}

void	manage_file(t_data *data, char *file, int num)
{
	int		fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		error_handler("Error : cannot open file");

	check_size(fd, data, num);

	data->champs[num].code = ft_strnew(data->champs[num].size);
	read(fd, data->champs[num].code, data->champs[num].size);
	data->champs[num].code[data->champs[num].size] = '\0';
}

void	get_files(t_data *data, char **argv)
{
	int i;

	count_files(data, argv);
	if (data->count == 0)
		error_handler("Error : No players");
	data->champs = (t_champ *)malloc(sizeof(t_champ) * data->count);
//	data->champs[data->count] = NULL; // ??

	i = 0;

	while (argv[++i])
	{
		int	num;

		num = 0;
		if (argv[i][0] != '-')
		{
			manage_file(data, argv[i], num);
			num++;
		}
	}
}