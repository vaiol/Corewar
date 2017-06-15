/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 17:38:29 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:54:40 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	check_magic(t_champ *champ, char *content)
{
	unsigned char	magic[4];
	int				i;

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

int		check_prog_name(t_champ *champ, char *content, size_t sh)
{
	size_t i;

	i = 0;
	while (i < PROG_NAME_LENGTH)
	{
		champ->prog_name[i] = content[i + sh];
		i++;
	}
	if (!champ->prog_name[0])
		champ_error_handler("No champion name", champ->file_name);
	return (i);
}

int		check_prog_size(t_champ *champ, char *content, size_t sh)
{
	unsigned char	str[4];
	int				nbr;
	int				i;

	i = -1;
	while (++i < 4)
		str[i] = content[sh + i];
	nbr = char_to_int(str);
	if (nbr > CHAMP_MAX_SIZE)
		champ_error_handler("Is too large", champ->file_name);
	champ->prog_size = (unsigned)nbr;
	return (i);
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
