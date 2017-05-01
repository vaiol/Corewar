/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_put_signed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 19:48:02 by astepano          #+#    #+#             */
/*   Updated: 2017/04/02 19:48:03 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pf_put_conversion.h"

void		pf_put_signed(t_conversion *conv, long long number)
{
	size_t	margin;
	char	*nbr;

	margin = (size_t)(conv->sign || number < 0);
	nbr = ft_itoa_base(number, 10);
	if (conv->sign && number >= 0)
		nbr = pf_strjoinchr(nbr, conv->sign, 1, BEGIN);
	if (conv->apostrophe)
		nbr = pf_handle_apostrophe(nbr);
	nbr = pf_handle_precision(conv, nbr, (int)margin, margin);
	if (!conv->precision && !number)
		nbr = pf_strclear(nbr);
	nbr = pf_handle_minwidth(conv, nbr, margin);
	pf_putstr(nbr);
	free(nbr);
}
