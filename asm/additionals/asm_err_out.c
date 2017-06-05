/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_err_out.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 16:05:10 by astepano          #+#    #+#             */
/*   Updated: 2017/06/02 16:06:04 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

void			asm_err_out(t_file_struct *content, char *file)
{
	if (content->err_type == LEXICAL)
	{
		ft_printf("%s[%d:%d]\n", MSG_LEXICAL,
				asm_get_line(content->err_index, file),
				asm_get_place(content->err_index, file));
	}
	else if (content->err_type == SYNTAX)
	{
		ft_printf("%s[%.3d:%.3d]\n", MSG_SYNTAX,
				asm_get_line(content->err_index, file),
				asm_get_place(content->err_index, file));
	}
	else
		ft_printf("ERRRROR!\n");
}
