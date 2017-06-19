/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 17:31:44 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:55:03 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	error_handler(char *str)
{
	ft_printf("%s\n", str);
	exit(1);
}

void	champ_error_handler(char *str, char *champion)
{
	ft_printf("Error : %s %s\n", str, champion);
	exit(1);
}

void	error_handler_usage(void)
{
	ft_printf("usage :\n");
	ft_printf("corewar [-a] [-dump nbr] [-l] [-v] [-n nbr] [champion.cor]\n");
	ft_printf("flags :\n");
	ft_printf("%-15s: Graphic interface\n", "-v");
	ft_printf("%-15s: ", "-a");
	ft_printf("Prints output from \"aff\" (Default is to hide it)\n");
	ft_printf("%-15s: Display logs\n", "-l");
	ft_printf("%-15s: ", "-n nbr");
	ft_printf("Sets the number of the next player\n");
	ft_printf("%-15s: ", "-dump nbr");
	ft_printf("Dump the memory on the standard output at [nbr] cycle\n");
	exit(1);
}
