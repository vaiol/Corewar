/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 16:20:25 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:50:01 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	function_live(t_data *data, t_carr *carr)
{
	int		n;
//	char	*name;

	carr->live++;
	data->print.nbr_live++;
	n = -1;
	while (++n < data->count)
	{
		if (carr->op.args[0] == data->champs[n].nb_set)
		{
			data->champs[n].last_live = data->print.cycle;
			data->winner = n;
			if (data->fl.v == 0)
			{
//				ft_printf("A process shows that player %i ", carr->pn);
//				name = data->champs[carr->pn - 1].prog_name;
//				ft_printf("(%s) is alive\n", name);
			}
		}
	}
	print_function(data, carr);
}
