/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_handle_precision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 19:54:02 by astepano          #+#    #+#             */
/*   Updated: 2017/04/02 19:54:03 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pf_handle.h"

char	*pf_handle_precision(t_conversion *c, char *str, int l, size_t m)
{
	int	count;

	count = c->precision - ((int)ft_strlen(str) - l);
	if (count > 0)
		str = pf_strjoinchr_begin(str, '0', count, m);
	return (str);
}
