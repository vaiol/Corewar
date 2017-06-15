/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_champs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 17:31:44 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:55:08 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	find_cor(t_data *data, char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
	{
		if (ft_strcmp(tab[i], "cor") == 0)
		{
			data->count++;
			return ;
		}
	}
}

void	count_champs(t_data *data, char **argv)
{
	int		i;
	char	**split;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] != '-')
		{
			split = ft_strsplit(argv[i], '.');
			if (ft_arrlen(split) > 1)
				find_cor(data, split);
			ft_arrdel(split);
		}
		i++;
	}
	if (data->count > 4)
		error_handler("Error : To much players");
	if (data->count == 0)
		error_handler("Error : No players");
	data->champs = (t_champ *)malloc(sizeof(t_champ) * data->count);
}
