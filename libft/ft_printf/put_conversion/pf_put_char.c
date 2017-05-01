/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_put_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 19:45:08 by astepano          #+#    #+#             */
/*   Updated: 2017/04/02 19:45:10 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pf_put_conversion.h"

void	pf_put_char(t_conversion *conv, va_list valist)
{
	int		char_len;
	int		count;
	char	chr;

	char_len = 1;
	if (conv->type != 'c')
		chr = conv->type;
	else if (conv->size == L)
		chr = (char)va_arg(valist, wint_t);
	else
		chr = va_arg(valist, int);
	count = conv->minimum_width - char_len;
	if (count > 0)
	{
		if (conv->padding == '-')
			pf_write(&chr, (size_t)char_len--);
		while (count--)
		{
			if (conv->padding == '0')
				pf_write("0", 1);
			else
				pf_write(" ", 1);
		}
	}
	pf_write(&chr, (size_t)char_len);
}
