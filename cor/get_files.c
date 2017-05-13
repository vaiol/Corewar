#include "corewar.h"

int		get_magic(unsigned char *str)
{
	int magic;

	magic = str[0] << 24;
	magic += str[1] << 16;
	magic += str[2] << 8;
	magic += str[3];
	return (magic);
}

void	check_magic(t_champ *champ, char *content)
{
	unsigned char	magic[4];
	int i;

	i = 0;
	while (i < 4)
	{
		magic[i] = content[i];
		i++;
	}
	magic[i] = '\0';
	champ->magic = get_magic(magic);
	if (COREWAR_EXEC_MAGIC != champ->magic)
		champ_error_handler("Wrong magic number", champ->file_name);
}

int		check_prog_name(t_champ *champ, char *content, size_t shift)
{
	size_t i;

	i = 0;
	while (i < PROG_NAME_LENGTH)
	{
		champ->prog_name[i] = content[i + shift];
		i++;
	}
	if (!champ->prog_name[0])
		champ_error_handler("No champion name", champ->file_name);
	return (i);
}

void	check_prog_size(t_champ *champ, char *content, size_t shift)
{
	champ->prog_size = (unsigned)content[shift];
	if (champ->prog_size > CHAMP_MAX_SIZE)
		champ_error_handler("Is too large", champ->file_name);
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
	if (!champ->comment[0])
		champ_error_handler("No champion comment", champ->file_name);
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
	check_magic(champ, content);
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
		champ_error_handler("Cannot open file", argv);

	size = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	if (size < 0)
		champ_error_handler("File is not valid", argv);

	content = ft_strnew((size_t)size);
	read(fd, content, (size_t)size);
//	content[(size_t)size] = '\0'; // ????

	data->champs->nb = nb;
	data->champs->file_name = argv;

	champ_check(&data->champs[nb], content);
	free(content);
}

void	get_files(t_data *data, char **argv)
{
	int i;
	int	nb;

	count_files(data, argv);
	if (data->count == 0)
		error_handler("Error : No players");
	data->champs = (t_champ *)malloc(sizeof(t_champ) * data->count);

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
