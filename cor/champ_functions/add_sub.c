/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 16:20:25 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:49:34 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	func_add_sub(t_data *data, t_carr *carr, int *args, int nb)
{
	if (nb == 4)
		carr->reg[args[2]] = carr->reg[args[0]] + carr->reg[args[1]];
	else
		carr->reg[args[2]] = carr->reg[args[0]] - carr->reg[args[1]];
	print_function(data, carr);
	manage_carry(carr, carr->reg[args[2]]);
}
