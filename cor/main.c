#include "corewar.h"

void	create_data(t_data *data)
{
	data->index = 1;
	data->count = 0;

	data->fl.flags = 0;
	data->fl.n = 0;
}

//4 - magic
//129 - name
//4 - prog_size


int		main(int argc, char **argv)
{
	t_data data;

	create_data(&data);

//	look for flags and save them to data->fl + add flag "flags";
	check_flags(argc, argv, &data);
//	check files for size, min/max number and save them to struct arr data->champs;
	get_files(&data, argv);


	t_file_struct file;


	size_t i;
	size_t shift = sizeof(unsigned int);

	i = 0;
	while (i < PROG_NAME_LENGTH)
	{
		file.prog_name[i] = data.champs[0].code[i + shift];
		i++;
	}
	shift = i + shift + sizeof(file.prog_size) + 3;
	file.prog_size = (unsigned)data.champs[0].code[shift];
	shift++;
	i = 0;
	while (i < COMMENT_LENGTH)
	{
		file.comment[i] = data.champs[0].code[i + shift];
		i++;
	}
	file.program = (char *)malloc(sizeof(char) * (file.prog_size + 1));
	shift = i + shift + 4;
	i = 0;
	while (i < file.prog_size)
	{
		file.program[i] = data.champs[0].code[i + shift];
		i++;
	}
	ft_printf("name: %s\ncomment: %s\nsize: %u\nprogram: ", file.prog_name, file.comment, file.prog_size);
	ft_print_memory(file.program, file.prog_size);



//	ft_printf("size: %llu\n", data.champs[0].size);
//	i = 0;
//	while (i < data.champs[0].size)
//	{
//		ft_printf("%d ", data.champs[0].code[i]);
//		i++;
//	}
//	while (data.champs[0].code[i])
//	{
//		ft_printf("%i", (int)data.champs[0].code[i]);
//		i++;
//	}

//	ft_printf("%s\n", data.champs[0].code);
//	data.champs[0].code;
//	ft_print_memory(data.champs[0].code, data.champs[0].size);


	return (0);
}