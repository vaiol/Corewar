#include "corewar.h"

// add new flags here!

void	get_flags(t_fl *fl, char c)
{
	if (c == 'n')
		fl->n = 1;
	else if (c == 'v')
		fl->v = 1;
	else
		error_handler("usage: corewar [-nv] [file ...]");
	fl->flags++;
}

char	*get_arg(t_data *data, int argc, char **argv)
{
	char *arg;

	arg = NULL;

	if (data->index >= argc)
		return (NULL);
	while (argv[data->index][0] != '-')
	{
		if (data->index + 1 >= argc)
			return (NULL);
		data->index++;
	}
	if (argv[data->index][1] == '\0')
		error_handler("usage: corewar [-nv] [file ...]");
	else
		arg = argv[data->index];
	data->index++;
	return (arg);
}


//parsing and adding flags to DATA

void	check_flags(int argc, char **argv, t_data *data)
{
	int		i;
	int		len;
	char	*arg;

	if (argc == 1)
		return ;
	while ((arg = get_arg(data, argc, argv)) != NULL)
	{
		i = 1;
		len = ft_strlen(arg);
		while (i < len)
		{
			get_flags(&data->fl, arg[i]);
			i++;
		}
	}
}
