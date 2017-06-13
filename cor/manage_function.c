/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 17:01:58 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:55:32 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	manage_carry(t_carr *carr, int res)
{
	if (res == 0)
		carr->carry = TRUE;
	else
		carr->carry = FALSE;
}

int		get_indirect_from_map(t_map *map, int index)
{
	unsigned char	str[4];
	int				nbr;

	if (index > MEM_SIZE)
		index = (index % MEM_SIZE);
	str[0] = map[index].cell;
	str[1] = map[index + 1].cell;
	str[2] = map[index + 2].cell;
	str[3] = map[index + 3].cell;
	nbr = char_to_int(str);
	return (nbr);
}

void	place_on_map(t_carr *carr, t_map *map, int nbr, int index)
{
	int				i;
	int				pos;
	unsigned char	*bytes;

	bytes = int_to_str(nbr);
	index = carr->index + (index % IDX_MOD);
//	if (index > 0)
		index = index % MEM_SIZE;
//	if (index < 0)
//		index = MEM_SIZE + (index % MEM_SIZE);
	i = -1;
	while (++i < 4)
	{
		pos = index + i;
		if (pos < 0)
			pos = MEM_SIZE + pos;
		map[pos].cell = bytes[i];
		map[pos].pn = carr->pn;
	}
	free(bytes);
}

void	get_wait_cycle(t_carr *carr)
{
	int i;

	i = -1;
	while (++i < OP_COUNT)
	{
		if (g_op_tab[i].opcode == carr->op.opcode)
		{
			carr->op.cycles = g_op_tab[i].cycles - 1;
			if ((int)carr->op.cycles < 0)
				carr->op.cycles = 0;
			return ;
		}
	}
	error_handler("Error : no opcode");
}

void	manage_function(t_data *data, t_carr *carr)
{
	if (carr->op.opcode == 1)
		function_live(data, carr);
	if (carr->op.opcode == 2)
		function_ld(data, carr, carr->op.args);
	if (carr->op.opcode == 3)
		function_st(data, carr);
	if (carr->op.opcode == 4 || carr->op.opcode == 5)
		func_add_sub(data, carr, carr->op.args, (int)carr->op.opcode);
	if (carr->op.opcode == 6 || carr->op.opcode == 7 || carr->op.opcode == 8)
		func_and_or(data, carr, carr->op.args, (int)carr->op.opcode);
	if (carr->op.opcode == 9)
		function_zjmp(data, carr);
	if (carr->op.opcode == 10)
		function_ldi(data, carr, carr->op.args);
	if (carr->op.opcode == 13)
		function_lld(data, carr, carr->op.args);
	if (carr->op.opcode == 14)
		function_lldi(data, carr, carr->op.args);
	if (carr->op.opcode == 11)
		function_sti(data, carr, carr->op.args);
	if (carr->op.opcode == 16)
		function_aff(data, carr);
}
