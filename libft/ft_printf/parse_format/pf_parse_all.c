/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 19:30:18 by astepano          #+#    #+#             */
/*   Updated: 2017/04/02 19:30:19 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pf_parse_all.h"

static t_conversion	*create_conversion(void)
{
	t_conversion	*conversion;

	conversion = (t_conversion *)malloc(sizeof(t_conversion));
	conversion->precision = -1;
	conversion->minimum_width = 0;
	conversion->hashtag = 0;
	conversion->apostrophe = 0;
	conversion->padding = '\0';
	conversion->sign = '\0';
	conversion->type = '\0';
	conversion->size = N;
	conversion->ldouble = '\0';
	return (conversion);
}

size_t				pf_parse(const char *f, size_t i, va_list valist)
{
	size_t			tmp;
	t_conversion	*form;

	if (f[i - 1] == '{')
		return (pf_parse_brace(f, i, valist));
	form = create_conversion();
	tmp = 0;
	while (f[i] && tmp != i)
	{
		tmp = i;
		i = pf_parse_flags(f, i, form);
		i = pf_parse_minwidth(f, i, form, valist);
		i = pf_parse_precision(f, i, form, valist);
		i = pf_parse_size(f, i, form);
	}
	if (f[i])
	{
		i = pf_parse_type(f, i, form);
		pf_put_conversion(form, valist);
	}
	free(form);
	return (i);
}
