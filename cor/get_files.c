#include "corewar.h"

//void	check_size(int fd, t_data *data, int num)
//{
//	off_t	size;
//	int		real_size;
//
//	size = lseek(fd, 0, SEEK_END);
//	lseek(fd, 0, SEEK_SET);
//	if (size < 0)
//		error_handler("Error : file is not valid");
//
//	real_size = (size_t)size - PROG_NAME_LENGTH - COMMENT_LENGTH;
//	ft_printf("%i\n", real_size);
//
//	if (real_size < 0)
//		error_handler("Error : champ is not valid");
//
//	if (real_size > CHAMP_MAX_SIZE)
//		error_handler("Error : champion is too large");
//	data->champs[num].size = (size_t)size;
//}

void	check_magic(t_file_struct *file, char *content, size_t shift)
{
	file->magic = (unsigned)content[shift];

	// compare with COREWAR_EXEC_MAGIC ?

}

int		check_prog_name(t_file_struct *file, char *content, size_t shift)
{
	size_t i;

	file->prog_name = ft_strnew(PROG_NAME_LENGTH);
	i = 0;
	while (i < PROG_NAME_LENGTH)
	{
		file->prog_name[i] = content[i + shift];
		i++;
	}
	if (!file->prog_name)
		error_handler("Error : No champion name");
	return (i);
}

void	check_prog_size(t_file_struct *file, char *content, size_t shift)
{
	file->prog_size = (unsigned)content[shift];
	if (file->prog_size > CHAMP_MAX_SIZE)
		error_handler("Error : champion is too large");
}

int		check_comment(t_file_struct *file, char *content, size_t shift)
{
	size_t i;

	file->comment= ft_strnew(COMMENT_LENGTH);
	i = 0;
	while (i < COMMENT_LENGTH)
	{
		file->comment[i] = content[i + shift];
		i++;
	}
	if (!file->comment)
		error_handler("Error : No champion comment");
	return (i);
}

void	check_program(t_file_struct *file, char *content, size_t shift, t_champ *champ)
{
	size_t i;

	i = 0;
	champ->program = ft_strnew(file->prog_size + 1);
	while (i < file->prog_size)
	{
		champ->program[i] = content[i + shift];
		i++;
	}
}

void	champ_check(t_file_struct *file, char *content, t_champ *champ)
{

	size_t i;
	size_t shift;

	shift = sizeof(unsigned int);
	check_magic(file, content, shift);
	i = check_prog_name(file, content, shift);
	shift = i + shift + sizeof(file->prog_size) + 3;
	check_prog_size(file, content, shift);
	i = check_comment(file, content, shift);
	shift = i + shift + 4;
	check_program(file, content, shift, champ);
/////////////////////////////////////////////////////
	ft_printf("name: %s\ncomment: %s\nsize: %u\nprogram: ", file->prog_name, file->comment, file->prog_size);
	ft_print_memory(champ->program, file->prog_size);
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

	champ_check(data->champs[nb].file, content, &data->champs[nb]);
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