/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_put.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 19:15:26 by astepano          #+#    #+#             */
/*   Updated: 2017/04/02 19:15:28 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PF_PUT_H
# define PF_PUT_H

# include <unistd.h>

size_t	g_count;
int		g_fd;

int		pf_printed_count(void);
void	pf_write(const void *buf, size_t nbyte);
void	pf_putstr(char const *s);

#endif
