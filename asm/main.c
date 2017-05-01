#include "asm.h"

void	error(char *error)
{
	ft_printf("{fd}%s\n", 2, error);
	exit(1);
}

int		parse_argumets(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_strequ(argv[i], "-c"))
			return (i);
		i++;
	}
	return (-1);
}

int		str_is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t'
		 && str[i] != '\n' && str[i] != '\v'
		 && str[i] != '\f' && str[i] != '\r')
			return (0);
	}
	return (1);
}

int		compare_str(char *str, char *str2)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t'
		   || str[i] == '\n' || str[i] == '\v'
		   || str[i] == '\f' || str[i] == '\r')
		i++;
	j = 0;
	while (str[i] == str[j])
	{
		i++;
		j++;
	}
	if (str[j])
		return (0);
	return (1);
}

void	validate_name(char **file)
{
	int i;
	int j;

	i = 0;
	while (str_is_empty(file[i]))
		i++;
	if (compare_str(file[i], ".name"))


}

void validation(char **file)
{
	validate_name(file);
}

void	parse_file(char *file_name)
{

	char	**file;

	if (!(file = read_file(file_name)))
		return ;
	validation(file);
	ft_arrdel(file);
}

void	parse_files(char **files)
{
	int arg;
	int	i;

	arg = parse_argumets(files);
	i = 0;
	while (files[i])
	{
		if (arg != -1 && i != arg)
			parse_file(files[i]);
		i++;
	}
	if (arg == -1)
		parse_file(files[i - 1]);
}

int		main(int argc, char **argv)
{
	if (argc == 1)
		error("Not enough files!");
	parse_files(argv + 1);
	return (0);
}