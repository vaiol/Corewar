/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 16:55:55 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:49:52 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	function_fork(t_data *data, t_carr *carr, unsigned opcode)
{
	int index;

	index = 0;
	if (opcode == 12)
		index = (carr->index - carr->t_ind) + (carr->op.args[0] % IDX_MOD);
	if (opcode == 15)
	{
		index = (carr->index - carr->t_ind) + carr->op.args[0];
		if (index > 0)
			index = index % MEM_SIZE;
		if (index < 0)
			index = MEM_SIZE + (index % MEM_SIZE);
	}
	if (index > MEM_SIZE)
		index = index % MEM_SIZE;
	print_function(data, carr);
	fork_carriage(data, carr, index);
}
