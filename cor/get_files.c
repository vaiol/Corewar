#include "corewar.h"

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
	champ->magic = char_to_int(magic);
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

void	check_prog_size(t_champ *champ, size_t shift)
{
	champ->prog_size = champ->real_prog_size - shift;
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
	i = check_comment(champ, content, shift);
	shift = i + shift + 5;
	check_prog_size(champ, shift);
	check_program(champ, content, shift);

/////////////////////////////////////////////////////
//	print champion info

//	ft_printf("name: %s\ncomment: %s\nsize: %u\nstart_pos: %i\n champ_number :%i\nprogram: ", champ->prog_name, champ->comment, champ->prog_size, champ->start_pos, champ->nb);
//	ft_print_memory(champ->program, champ->prog_size);
}

void	set_start_pos(t_data *data, t_champ *champ, int nb)
{
	int x;

	x = MEM_SIZE / data->count;
	champ->start_pos = x * (nb);
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
	data->champs[nb].nb = nb + 1;
	set_start_pos(data, &data->champs[nb], nb);
	data->champs->file_name = argv;
	data->champs[nb].real_prog_size = (size_t)size;
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
	nb = 0;
	i = 0;
	while (argv[++i])
	{
		if (argv[i][0] != '-')
		{
			manage_file(data, argv[i], nb);
			nb++;
		}
	}
}
