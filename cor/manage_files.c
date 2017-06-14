/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 17:40:56 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:55:28 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	champ_check(t_champ *champ, char *content)
{
	size_t i;
	size_t shift;

	shift = sizeof(unsigned int);
	check_magic(champ, content);
	i = (size_t)check_prog_name(champ, content, shift);
	shift = i + shift + sizeof(champ->prog_size) + 3;
	i = check_comment(champ, content, shift);
	shift = i + shift + 5;
	check_prog_size(champ, shift);
	check_program(champ, content, shift);
}

void	manage_file(t_data *data, char *argv, int nb)
{
	int		fd;
	off_t	size;
	char	*content;

	if ((fd = open(argv, O_RDONLY)) == -1)
		champ_error_handler("Cannot open file", argv);
	size = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	if (size < 0)
		champ_error_handler("File is not valid", argv);
//	if (data->champs[nb].nb_set == 0)
//		set_default_num(data, nb, -1);
	content = ft_strnew((size_t)size);
	read(fd, content, (size_t)size);
	data->champs[nb].nb = nb + 1;
//	set_start_pos(data, &data->champs[nb], nb);
	data->champs->file_name = argv;
	data->champs[nb].real_prog_size = (size_t)size;
	champ_check(&data->champs[nb], content);
	free(content);
	data->nb++;
}
