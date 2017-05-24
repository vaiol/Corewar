/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_validate_content.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 15:22:44 by astepano          #+#    #+#             */
/*   Updated: 2017/05/24 15:22:45 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	asm_validate_content(t_file_struct *content)
{
	char	*error;

	if (!content)
	{
		ft_printf("Syntax error!");
		return (0);
	}
	if (content->comment == NULL || content->prog_name == NULL)
	{
		ft_printf("Lexical error!");
		return (0);
	}
	if ((error = asm_validate_operations(content)))
	{
		ft_printf("%s\n", error);
		free(error);
		return (0);
	}
	return (1);
}
