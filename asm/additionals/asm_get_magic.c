/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_get_magic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 15:33:58 by astepano          #+#    #+#             */
/*   Updated: 2017/05/24 15:34:00 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

void	asm_get_magic(t_file_struct *content, unsigned int n)
{
	content->magic[0] = (n >> 24) & 0xFF;
	content->magic[1] = (n >> 16) & 0xFF;
	content->magic[2] = (n >> 8) & 0xFF;
	content->magic[3] = n & 0xFF;
}
