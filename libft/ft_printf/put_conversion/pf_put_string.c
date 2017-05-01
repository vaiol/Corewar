/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_put_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 19:48:11 by astepano          #+#    #+#             */
/*   Updated: 2017/04/02 19:48:12 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pf_put_conversion.h"

void		pf_put_string(t_conversion *conv, va_list valist)
{
	char	*str;

	if (conv->size == L)
		str = pf_wstrtostr(va_arg(valist, wchar_t *), conv->precision);
	else
	{
		if (!(str = va_arg(valist, char *)))
			str = ft_strdup("(null)");
		else
			str = ft_strdup(str);
	}
	str = ft_strcut(str, conv->precision);
	conv->precision = -1;
	str = pf_handle_minwidth(conv, str, 0);
	pf_putstr(str);
	free(str);
}
