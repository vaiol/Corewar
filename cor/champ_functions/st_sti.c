/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 16:27:12 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:50:05 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	function_st(t_data *data, t_carr *carr)
{
//	int				i;
	int				index;
//	unsigned char	*bytes;

	if (carr->arg_type[1] == T_IND)
	{
//		bytes = int_to_str(carr->reg[carr->op.args[0]]);
//		index = carr->index + (carr->op.args[1] % IDX_MOD);
		index = carr->op.args[1];
		place_on_map(carr, data->map, carr->reg[carr->op.args[0]], index);
//		i = -1;
//		while (++i < 4)
//		{
//			data->map[index + i].cell = bytes[i];
//			data->map[index + i].pn = carr->pn;
//		}
//		free(bytes);
	}
	else if (carr->arg_type[1] == T_REG)
		carr->reg[carr->op.args[1]] = carr->reg[carr->op.args[0]];
	print_function(data, carr);
}

void	function_sti(t_data *data, t_carr *carr, int *args)
{
	int res;
	int argv[2];
	int index;

	if (carr->arg_type[1] == T_REG)
		argv[0] = carr->reg[args[1]];
	else if (carr->arg_type[1] == T_DIR)
		argv[0] = args[1];
	else if (carr->arg_type[1] == T_IND)
	{
		index = carr->index + (args[0] % IDX_MOD);
		argv[0] = get_indirect_from_map(data->map, index);
	}
	if (carr->arg_type[2] == T_REG)
		argv[1] = carr->reg[args[2]];
	else if (carr->arg_type[2] == T_DIR)
		argv[1] = args[2];
	res = argv[0] + argv[1];
	print_function(data, carr);
	place_on_map(carr, data->map, carr->reg[args[0]], res);
}
