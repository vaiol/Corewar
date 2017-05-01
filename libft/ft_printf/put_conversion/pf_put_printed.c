/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_put_printed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 19:47:49 by astepano          #+#    #+#             */
/*   Updated: 2017/04/02 19:47:51 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pf_put_conversion.h"

void	pf_put_printed(t_conversion *conv, va_list valist)
{
	void	*n;

	n = va_arg(valist, void *);
	if (conv->size == N)
		*((int *)n) = pf_printed_count();
	else if (conv->size == HH)
		*((char *)n) = (char)pf_printed_count();
	else if (conv->size == H)
		*((short *)n) = (short)pf_printed_count();
	else if (conv->size == L)
		*((long *)n) = pf_printed_count();
	else if (conv->size == LL)
		*((long long *)n) = pf_printed_count();
	else if (conv->size == Z)
		*((ssize_t *)n) = pf_printed_count();
	else if (conv->size == J)
		*((intmax_t *)n) = pf_printed_count();
}
