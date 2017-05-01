/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 20:43:18 by astepano          #+#    #+#             */
/*   Updated: 2017/03/07 20:43:25 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *restrict format, ...)
{
	size_t		len;
	size_t		i;
	va_list		valist;

	if (!format)
		return (-1);
	va_start(valist, format);
	len = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%' || format[i] == '{')
		{
			pf_write(format + len, i - len);
			len = pf_parse(format, i + 1, valist);
			i = len - 1;
		}
		i++;
	}
	pf_write(format + len, i - len);
	va_end(valist);
	return (pf_printed_count());
}
