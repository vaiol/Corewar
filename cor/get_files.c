#include "corewar.h"

void	check_magic(t_champ *champ, char *content, size_t shift)
{
	char	magic_hex[5];

	int i = 0;

	while (i < 4)
	{
		magic_hex[i] = content[i];
		i++;
	}
	magic_hex[i] = '\0';


	int res;
	res = ft_memcmp(magic_hex, (void *)COREWAR_EXEC_MAGIC, 3);
	ft_printf("res = %i\n", res);



	ft_printf("hex : %s\n", magic_hex);

	champ->magic = (unsigned)content[0];





	ft_printf("magic: %u\n", champ->magic);
	ft_printf("Magic: %u\n", COREWAR_EXEC_MAGIC);

	// compare with COREWAR_EXEC_MAGIC ?

	if (COREWAR_EXEC_MAGIC == champ->magic)
	{
		ft_printf("Done\n");
	}
	else
	{
		ft_printf("Wrong\n");
	}

	shift++;

}

int		check_prog_name(t_champ *champ, char *content, size_t shift)
{
	size_t i;

//	champ->prog_name = ft_strnew(PROG_NAME_LENGTH);
	i = 0;
	while (i < PROG_NAME_LENGTH)
	{
		champ->prog_name[i] = content[i + shift];
		i++;
	}
//	if (!champ->prog_name)
//		error_handler("Error : No champion name");
	return (i);
}

void	check_prog_size(t_champ *champ, char *content, size_t shift)
{
	champ->prog_size = (unsigned)content[shift];
	if (champ->prog_size > CHAMP_MAX_SIZE)
		error_handler("Error : champion is too large");
}

int		check_comment(t_champ *champ, char *content, size_t shift)
{
	size_t i;

	i = 0;
	while (i < COMMENT_LENGTH)
	{
		champ->comment[i] = content[i + shift];
		i++;
	}
//	if (!champ->comment)
//		error_handler("Error : No champion comment");
	return (i);
}

void	check_program(t_champ *champ, char *content, size_t shift)
{
	size_t i;

	i = 0;
	champ->program = ft_strnew(champ->prog_size + 1);
	while (i < champ->prog_size)
	{
		champ->program[i] = content[i + shift];
		i++;
	}
}

void	champ_check(t_champ *champ, char *content)
{

	size_t i;
	size_t shift;

	shift = sizeof(unsigned int);
	check_magic(champ, content, shift);
	i = check_prog_name(champ, content, shift);
	shift = i + shift + sizeof(champ->prog_size) + 3;
	check_prog_size(champ, content, shift);
	i = check_comment(champ, content, shift);
	shift = i + shift + 4;
	check_program(champ, content, shift);
/////////////////////////////////////////////////////
	ft_printf("name: %s\ncomment: %s\nsize: %u\nprogram: ", champ->prog_name, champ->comment, champ->prog_size);
	ft_print_memory(champ->program, champ->prog_size);
}

void	manage_file(t_data *data, char *argv, int nb)
{
	int		fd;
	off_t	size;
	char 	*content;

	if ((fd = open(argv, O_RDONLY)) == -1)
		error_handler("Error : cannot open file");

	size = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	if (size < 0)
		error_handler("Error : file is not valid");

	content = ft_strnew((size_t)size);
	read(fd, content, (size_t)size);
	content[(size_t)size] = '\0'; // ????

	data->champs->nb = nb;

	champ_check(&data->champs[nb], content);
	free(content);
}


void	get_files(t_data *data, char **argv)
{
	int i;
	int	nb;

//	count_files(data, argv);
	count_files(data, argv);
	if (data->count == 0)
		error_handler("Error : No players");
	data->champs = (t_champ *)malloc(sizeof(t_champ) * data->count);
//	data->champs[data->count] = NULL; // ??

	i = 0;
	while (argv[++i])
	{
		nb = 0;
		if (argv[i][0] != '-')
		{
			manage_file(data, argv[i], nb);
			nb++;
		}
	}
}