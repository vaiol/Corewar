/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_put_conversion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 19:45:27 by astepano          #+#    #+#             */
/*   Updated: 2017/04/02 19:45:29 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pf_put_conversion.h"

static unsigned long long	get_unsigned(t_conversion *conv, va_list valist)
{
	unsigned long long	result;

	result = 0;
	if (conv->size == N)
		result = va_arg(valist, unsigned int);
	else if (conv->size == HH)
		result = (unsigned char)va_arg(valist, int);
	else if (conv->size == H)
		result = (unsigned short)va_arg(valist, int);
	else if (conv->size == L)
		result = va_arg(valist, unsigned long);
	else if (conv->size == LL)
		result = va_arg(valist, unsigned long long);
	else if (conv->size == Z)
		result = va_arg(valist, size_t);
	else if (conv->size == J)
		result = va_arg(valist, uintmax_t);
	return (result);
}

static long long			get_signed(t_conversion *conv, va_list valist)
{
	long long	result;

	result = 0;
	if (conv->size == N)
		result = va_arg(valist, int);
	else if (conv->size == HH)
		result = (char)va_arg(valist, int);
	else if (conv->size == H)
		result = (short)va_arg(valist, int);
	else if (conv->size == L)
		result = va_arg(valist, long);
	else if (conv->size == LL)
		result = va_arg(valist, long long);
	else if (conv->size == Z)
		result = va_arg(valist, ssize_t);
	else if (conv->size == J)
		result = va_arg(valist, intmax_t);
	return (result);
}

void						pf_put_conversion(t_conversion *conv,
		va_list valist)
{
	if (conv->type == 's')
		pf_put_string(conv, valist);
	else if (ft_strcchr("di", (char)conv->type))
		pf_put_signed(conv, get_signed(conv, valist));
	else if (ft_strcchr("ouxXbk", (char)conv->type))
		pf_put_unsigned(conv, get_unsigned(conv, valist));
	else if (conv->type == 'p')
		pf_put_memory(conv, valist);
	else if (conv->type == 'n')
		pf_put_printed(conv, valist);
	else if (ft_strcchr("fFeEgGaA", (char)conv->type))
		pf_put_float(conv, valist);
	else if (conv->type == 'r')
		pf_put_unprintable(conv, valist);
	else
		pf_put_char(conv, valist);
}
