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
	ft_printf("usage: corewar [-alv] [file ...]\n");
	exit(1);
}
