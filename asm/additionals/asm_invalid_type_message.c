/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_invalid_type_message.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 15:34:21 by astepano          #+#    #+#             */
/*   Updated: 2017/05/24 15:34:22 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

char		*asm_invalid_type_message(t_operation *op, int number)
{
	char	*type;
	int		count;
	char	*err;

	count = asm_is_arg(op->args[number]);
	type = "undefined";
	if (count == T_REG)
		type = "register";
	else if (count == T_DIR || count == T_LAB)
		type = "direct";
	else if (count == T_IND)
		type = "indirect";
	err = ft_strfjoin("Invalid parameter ", ft_itoa(number), SECOND);
	err = ft_strfjoin(err, " type ", FIRST);
	err = ft_strfjoin(err, type, FIRST);
	err = ft_strfjoin(err, " for instruction ", FIRST);
	err = ft_strfjoin(err, op->name, FIRST);
	return (err);
}
