/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_function.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 17:43:57 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:56:08 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		validate_a(t_carr *carr, unsigned opcode)
{
	if (opcode == 1 || opcode == 9 || opcode == 12 || opcode == 15)
	{
		if (carr->op.count_args == 1 && carr->arg_type[0] == T_DIR)
			return (TRUE);
	}
	if (opcode == 16)
	{
		if (carr->op.count_args == 1 && carr->arg_type[0] == T_REG)
			return (TRUE);
	}
	if (opcode == 4 || opcode == 5)
	{
		if (carr->op.count_args == 3)
			if (carr->arg_type[0] == T_REG &&
				carr->arg_type[1] == T_REG &&
				carr->arg_type[2] == T_REG)
				return (TRUE);
	}
	if (opcode == 6 || opcode == 7 || opcode == 8)
	{
		if (carr->op.count_args == 3)
			if (carr->arg_type[2] == T_REG)
				return (TRUE);
	}
	return (FALSE);
}

int		validate_b(t_carr *carr, unsigned opcode)
{
	if (opcode == 2 || opcode == 13)
	{
		if (carr->op.count_args == 2)
			if (carr->arg_type[0] == T_DIR || carr->arg_type[0] == T_IND)
				if (carr->arg_type[1] == T_REG)
					return (TRUE);
	}
	if (opcode == 3)
	{
		if (carr->op.count_args == 2)
			if (carr->arg_type[0] == T_REG)
				if (carr->arg_type[1] == T_IND || carr->arg_type[1] == T_REG)
					return (TRUE);
	}
	if (opcode == 10 || opcode == 14)
	{
		if (carr->op.count_args == 3)
			if (carr->arg_type[1] == T_DIR || carr->arg_type[1] == T_REG)
				if (carr->arg_type[2] == T_REG)
					return (TRUE);
	}
	return (FALSE);
}

int		validate_c(t_carr *carr, unsigned opcode)
{
	if (opcode == 11)
	{
		if (carr->op.count_args == 3)
			if (carr->arg_type[0] == T_REG)
				if (carr->arg_type[2] == T_DIR || carr->arg_type[2] == T_REG)
					return (TRUE);
	}
	return (FALSE);
}

int		validate_function(t_carr *carr, unsigned opcode)
{
	int i;

	i = -1;
	while (++i < 3)
	{
		if (carr->arg_type[i] == T_REG)
		{
			if (carr->op.args[i] < 1 || carr->op.args[i] > 16)
				return (FALSE);
		}
	}
	if (validate_a(carr, opcode) == TRUE)
		return (TRUE);
	if (validate_b(carr, opcode) == TRUE)
		return (TRUE);
	if (validate_c(carr, opcode) == TRUE)
		return (TRUE);
	return (FALSE);
}
