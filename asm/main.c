/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 15:25:26 by astepano          #+#    #+#             */
/*   Updated: 2017/05/24 15:25:28 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

//TODO Usage...
//TODO -a flag
//TODO Error message when wrong file

static int		parse_argumets(char **argv)
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
static void		parse_files(char **files)
{
	int arg;
	int	i;

	arg = parse_argumets(files);
	i = 0;
	while (files[i])
	{
		if (arg != -1 && i != arg)
			asm_generate_byte_code(asm_parse_content_file(files[i]));
		i++;
	}
	if (arg == -1)
		asm_generate_byte_code(asm_parse_content_file(files[i - 1]));
}

int				main(int argc, char **argv)
{
	if (argc == 1)
		ft_printf("Not enough files!");
	parse_files(argv + 1);
	return (0);
}
