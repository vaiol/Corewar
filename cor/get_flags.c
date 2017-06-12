#include "corewar.h"

// add new flags here!

//void	get_flags(t_fl *fl, char c)
//{
//	if (c == 'v')
//		fl->v = 1;
//	else if (c == 'l')
//		fl->l = 1;
//	else if (c == 'a')
//		fl->a = 1;
//	else
//		error_handler_usage();
//	fl->flags++;
//}

//void	get_flags(t_data *data, t_fl *fl, char *flag)
//{
//	if (ft_strcmp(flag, "-dump") == 0)
//


//	if (c == 'v')
//		fl->v = 1;
//	else if (c == 'l')
//		fl->l = 1;
//	else if (c == 'a')
//		fl->a = 1;
//	else
//		error_handler_usage();
//	fl->flags++;
//}

//char	*get_arg(t_data *data, int argc, char **argv)
//{
//	char *arg;
//
//	arg = NULL;
//	if (data->index >= argc)
//		return (NULL);
//	while (argv[data->index][0] != '-')
//	{
//		if (data->index + 1 >= argc)
//			return (NULL);
//		data->index++;
//	}
//	if (argv[data->index][1] == '\0')
//		error_handler_usage();
//	else
//		arg = argv[data->index];
//	data->index++;
//	return (arg);
//}

//parsing and adding flags to DATA

//void	check_dump(t_data *data, int argc, char **argv)
//{
//	char	*arg;
//	int		i;
//	int		index;
//
//	index = 0;
//	if (data->index >= argc)
//		return ;
//	while (++index < argc)
//	{
//		if (ft_strcmp(argv[index], "-dump") == 0)
//		{
//			i = -1;
//			if (++index < argc)
//			{
//				while (++i < ft_strlen(argv[index]))
//				{
//					if (ft_isdigit(argv[index][i] == 0))
//						error_handler_usage();
//				}
////				if (ft_strlen(argv[index]) > 0)
//				data->dump = ft_atoi(argv[index]);
//			}
//		}
//	}
//}


void	check_dump(t_data *data, int argc, char **argv)
{
	int i;

	i = -1;
	if (++data->index < argc)
	{
		while (++i < (int)ft_strlen(argv[data->index]))
		{
			if (ft_isdigit(argv[data->index][i]) == 0)
				error_handler_usage();
		}
		data->dump = ft_atoi(argv[data->index]);
	}
	else
		error_handler_usage();
}

int 	is_number(char *str)
{
	int i;

	i = -1;

	while (++i < (int)ft_strlen(str))
	{
		if (str[0] == '-')
			i++;
		if (ft_isdigit(str[i]) == 0)
			return (FALSE);
	}
	return (TRUE);
}

void	set_player_nbr(t_data *data, int argc, char **argv)
{
	if (++data->index < argc)
	{
		if (is_number(argv[data->index]) == TRUE)
		{
			data->champs[data->nb].nb_set = ft_atoi(argv[data->index]);
			data->index++;
		}
		if (data->index < argc)
			manage_file(data, argv[data->index], data->nb);
		else
			error_handler_usage();
	}
	else
		error_handler_usage();
}

void	get_flag(t_data *data, int argc, char **argv)
{
	if (ft_strcmp(argv[data->index], "-dump") == 0)
		check_dump(data, argc, argv);
	else if (ft_strcmp(argv[data->index], "-n") == 0)
		set_player_nbr(data, argc, argv);
	else if (ft_strcmp(argv[data->index], "-v") == 0)
		data->fl.v = 1;
	else if (ft_strcmp(argv[data->index], "-l") == 0)
		data->fl.l = 1;
	else if (ft_strcmp(argv[data->index], "-a") == 0)
		data->fl.a = 1;
	else
		error_handler_usage();
}

void	check_flags(t_data *data, int argc, char **argv)
{
	if (data->index >= argc)
		return ;

	if (argv[data->index][0] == '-')
		get_flag(data, argc, argv);
	else
	{
		data->champs[data->nb].nb_set = 0;
		manage_file(data, argv[data->index], data->nb);
	}


	data->index++;
	check_flags(data, argc, argv);
}
//
//void	check_flags(int argc, char **argv, t_data *data)
//{
//	int		i;
//	int		len;
//	char	*arg;
//
//	if (argc == 1)
//		error_handler_usage();
//	while ((arg = get_arg(data, argc, argv)) != NULL)
//	{
//		i = 1;
//		len = (int)ft_strlen(arg);
//		while (i < len)
//		{
//			get_flags(&data->fl, arg[i]);
//			i++;
//		}
//	}
//}
