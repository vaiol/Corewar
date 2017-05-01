/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 19:30:44 by astepano          #+#    #+#             */
/*   Updated: 2017/04/02 19:30:45 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pf_parse_all.h"

size_t	pf_parse_flags(const char *f, size_t i, t_conversion *form)
{
	while (f[i])
	{
		if (f[i] == '#')
			form->hashtag = 2;
		else if (f[i] == '\'')
			form->apostrophe = 1;
		else if (f[i] == ' ')
			form->sign = form->sign == '+' ? form->sign : (char)' ';
		else if (f[i] == '+')
			form->sign = '+';
		else if (f[i] == '0')
			form->padding = form->padding == '-' ? form->padding : (char)'0';
		else if (f[i] == '-')
			form->padding = '-';
		else if (f[i] == 'L')
			form->ldouble = 1;
		else
			break ;
		i++;
	}
	return (i);
}
