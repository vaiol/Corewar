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

static void		parse_files(char **files)
{
	int	index;
	int arg;
	int	i;

	i = 0;
	arg = 0;
	index = 0;
	while (files[i])
	{
		if (ft_strequ(files[i], "-a"))
			arg = 1;
		else
			index = i;
		i++;
	}
	asm_generate_byte_code(asm_parse_content_file(files[index], arg));
}

int				main(int argc, char **argv)
{
	if (argc == 1)
	{
		ft_printf(MSG_USAGE);
		ft_printf(MSG_USAGE2);
		ft_printf(MSG_USAGE3);
		return (0);
	}
	if (argc == 2 && ft_strequ(argv[1], "-a"))
	{
		ft_printf("Can't read source file (null)\n");
		return (0);
	}
	parse_files(argv + 1);
	sleep(5);
	return (0);
}
