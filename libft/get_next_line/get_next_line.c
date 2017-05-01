/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 14:49:35 by astepano          #+#    #+#             */
/*   Updated: 2017/01/20 16:20:26 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(const int fd, char **line)
{
	static t_lines	*begin_list;

	if (read(fd, NULL, 0) < 0)
		return (-1);
	if (!gnl_createfd(&begin_list, fd))
	{
		*line = NULL;
		return (0);
	}
	*line = gnl_get_line(fd, &begin_list);
	if (*line)
		return (1);
	else
		return (0);
}
