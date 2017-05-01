/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 19:31:05 by astepano          #+#    #+#             */
/*   Updated: 2017/04/02 19:31:07 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pf_parse_all.h"

static void	set_size(t_conversion *form, t_size new)
{
	if (form->size >= new)
		return ;
	form->size = new;
}

size_t		pf_parse_size(const char *f, size_t i, t_conversion *form)
{
	if (f[i] == 'h')
	{
		if (f[i + 1] == 'h' && i++)
			set_size(form, HH);
		else
			set_size(form, H);
	}
	else if (f[i] == 'l')
	{
		if (f[i + 1] == 'l' && i++)
			set_size(form, LL);
		else
			set_size(form, L);
	}
	else if (f[i] == 'j')
		set_size(form, J);
	else if (f[i] == 'z')
		set_size(form, Z);
	else
		return (i);
	return (i + 1);
}
