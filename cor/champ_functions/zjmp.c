/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 16:41:23 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:50:09 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	function_zjmp(t_data *data, t_carr *carr)
{
	if (carr->carry == TRUE)
		carr->t_ind = (carr->op.args[0] % IDX_MOD);
	print_function(data, carr);
}
