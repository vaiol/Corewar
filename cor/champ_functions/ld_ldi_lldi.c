/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_ldi_lldi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 16:24:53 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:49:56 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	function_ld(t_data *data, t_carr *carr, int *args)
{
	int index;

	if (carr->arg_type[0] == T_DIR)
		carr->reg[args[1]] = args[0];
	else if (carr->arg_type[0] == T_IND)
	{
		index = carr->index + args[0];
		carr->reg[args[1]] = get_indirect_from_map(data->map, index);
	}
	print_function(data, carr);
	manage_carry(carr, carr->reg[args[1]]);
}

void	function_ldi(t_data *data, t_carr *carr, int *args)
{
	int res;
	int argv[2];
	int index;

	if (carr->arg_type[0] == T_REG)
		argv[0] = carr->reg[args[0]];
	else if (carr->arg_type[0] == T_DIR)
		argv[0] = args[0];
	else if (carr->arg_type[0] == T_IND)
	{
		index = carr->index + (args[0] % IDX_MOD);
		argv[0] = get_indirect_from_map(data->map, carr->index + index);
	}
	if (carr->arg_type[1] == T_REG)
		argv[1] = carr->reg[args[1]];
	else if (carr->arg_type[1] == T_DIR)
		argv[1] = args[1];
	res = argv[0] + argv[1];
	res = carr->index + (res % IDX_MOD);
	carr->reg[args[2]] = get_indirect_from_map(data->map, res);
	print_function(data, carr);
}

void	function_lld(t_data *data, t_carr *carr, int *args)
{
	int index;

	if (carr->arg_type[0] == T_DIR)
		carr->reg[args[1]] = args[0];
	else if (carr->arg_type[0] == T_IND)
	{
		index = carr->index + args[0];
		carr->reg[args[1]] = get_indirect_from_map(data->map, index);
	}
	print_function(data, carr);
	manage_carry(carr, carr->reg[args[1]]);
}

void	function_lldi(t_data *data, t_carr *carr, int *args)
{
	int res;
	int argv[2];

	if (carr->arg_type[0] == T_REG)
		argv[0] = carr->reg[args[0]];
	else if (carr->arg_type[0] == T_DIR)
		argv[0] = args[0];
	else if (carr->arg_type[0] == T_IND)
		argv[0] = get_indirect_from_map(data->map, carr->index + args[0]);
	if (carr->arg_type[1] == T_REG)
		argv[1] = carr->reg[args[1]];
	else if (carr->arg_type[1] == T_DIR)
		argv[1] = args[1];
	argv[0] = unsigned_to_int(argv[0]);
	res = argv[0] + argv[1];
	carr->reg[args[2]] = get_indirect_from_map(data->map, carr->index + res);
	print_function(data, carr);
	manage_carry(carr, carr->reg[args[2]]);
}
