/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opcode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 17:25:58 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:55:42 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	get_octal_coding(t_data *data, t_carr *carr, int i)
{
	carr->op.count_args = g_op_tab[i].count_args;
	carr->t_ind++;
	if (g_op_tab[i].octal_coding)
		parse_octal(data, carr, g_op_tab[i].label_size);
	else if (g_op_tab[i].octal_coding == 0)
		parse_non_octal(data, carr, g_op_tab[i].label_size);
	if (validate_function(carr, carr->op.opcode) == TRUE)
		carr->valid = TRUE;
}

int		get_opcode(t_data *data, t_carr *carr, int i)
{
	if ((unsigned int)data->map[carr->index].cell == g_op_tab[i].opcode)
	{
		carr->op.opcode = g_op_tab[i].opcode;
		carr->g_int = i;
		carr->op.name = g_op_tab[i].name;
		get_wait_cycle(carr);
		return (TRUE);
	}
	return (FALSE);
}

void	read_cell(t_data *data, t_carr *carr)
{
	int	i;

	i = 0;
	while (get_opcode(data, carr, i) != TRUE && i < OP_COUNT - 2)
		i++;
}
