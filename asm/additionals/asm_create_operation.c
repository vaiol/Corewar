/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_create_operation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 15:32:06 by astepano          #+#    #+#             */
/*   Updated: 2017/05/24 15:32:07 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

t_operation	*asm_create_operation(void)
{
	t_operation	*op;

	op = (t_operation *)malloc(sizeof(t_operation));
	op->args = NULL;
	op->label = NULL;
	op->name = NULL;
	op->index = -1;
	op->eof = 0;
	return (op);
}
