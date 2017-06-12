/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_xor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 16:40:30 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:49:47 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	func_and_or(t_data *data, t_carr *carr, int *args, int nb)
{
	int i;
	int argv[2];
	int index;

	i = -1;
	while (++i < 2)
	{
		if (carr->arg_type[i] == T_REG)
			argv[i] = carr->reg[args[i]];
		else if (carr->arg_type[i] == T_DIR)
			argv[i] = args[i];
		else if (carr->arg_type[i] == T_IND)
		{
			index = carr->index + args[i];
			argv[i] = get_indirect_from_map(data->map, index);
		}
	}
	if (nb == 6)
		carr->reg[args[2]] = argv[0] & argv[1];
	if (nb == 7)
		carr->reg[args[2]] = argv[0] | argv[1];
	if (nb == 8)
		carr->reg[args[2]] = argv[0] ^ argv[1];
	print_function(data, carr);
	manage_carry(carr, carr->reg[args[2]]);
}
