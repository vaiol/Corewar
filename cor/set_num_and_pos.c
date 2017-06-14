/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_num_and_pos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 17:42:33 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:55:54 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	set_start_pos(t_data *data, t_champ *champ, int nb)
{
	int x;

	x = MEM_SIZE / data->count;
	champ->start_pos = x * (nb);
}

void	set_default_num(t_data *data, int nb, int number)
{
	int n;

	n = -1;
	while (++n < data->count)
	{
		if (data->champs[n].nb_set == number)
		{
			set_default_num(data, nb, number - 1);
			return ;
		}
	}
	data->champs[nb].nb_set = number;
}
