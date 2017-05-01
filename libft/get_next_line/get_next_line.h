/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 14:49:50 by astepano          #+#    #+#             */
/*   Updated: 2017/01/20 15:42:04 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "../libft.h"

typedef struct		s_lines
{
	char			*content;
	int				fd;
	struct s_lines	*next;
}					t_lines;

int					gnl_createfd(t_lines **begin, int fd);
char				*gnl_get_line(int fd, t_lines **begin);

#endif
