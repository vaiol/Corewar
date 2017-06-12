/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 16:41:47 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:49:42 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	function_aff(t_data *data, t_carr *carr)
{
	if (data->fl.a == 1)
	{
		if (ft_isalnum(carr->op.args[0]))
			ft_printf("Aff: %c\n", carr->op.args[0]);
		else
			ft_printf("Aff: ?\n");
	}
}
