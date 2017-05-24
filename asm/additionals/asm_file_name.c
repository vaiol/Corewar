/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_file_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 15:32:39 by astepano          #+#    #+#             */
/*   Updated: 2017/05/24 15:32:44 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

char	*asm_file_name(char *str, char *file_name)
{
	str = ft_strsub(file_name, 0, ft_strlen(file_name) - 2);
	str = ft_strfjoin(str, ".cor", FIRST);
	return (str);
}
