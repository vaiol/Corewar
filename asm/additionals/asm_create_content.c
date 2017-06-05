/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_create_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 15:31:02 by astepano          #+#    #+#             */
/*   Updated: 2017/05/24 15:31:03 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

t_file_struct	*asm_create_content(void)
{
	t_file_struct	*content;

	content = (t_file_struct*)malloc(sizeof(t_file_struct));
	content->ops = NULL;
	content->comment = NULL;
	content->prog_name = NULL;
	content->file_name = NULL;
	content->coding_string = NULL;
	content->flag_print = 0;
	return (content);
}
