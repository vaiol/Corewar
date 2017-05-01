/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 19:26:12 by astepano          #+#    #+#             */
/*   Updated: 2017/04/02 19:26:15 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pf_util.h"

static char	*utoa_puthash(char *result, int hash, char size, int b)
{
	if (size == 'X' && hash)
	{
		result[0] = '0';
		if (b == 16)
			result[1] = 'X';
	}
	else if (ft_strcchr("xb", size) && hash)
	{
		result[0] = '0';
		if (b == 16)
			result[1] = 'x';
		if (b == 2)
			result[1] = 'b';
	}
	return (result);
}

char		*pf_utoa_base(unsigned long long value, int b, char size, int hash)
{
	char				*base;
	char				*result;
	unsigned long long	v;
	unsigned long long	tmp;
	int					len;

	if (size == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	len = (hash && ((b == 16) || (b == 2))) ? 3 : 1;
	len = (hash && (b == 8)) ? 2 : len;
	v = value;
	tmp = value;
	while ((tmp /= b))
		len++;
	result = (char *)malloc(sizeof(char) * (len + 1));
	result[len] = '\0';
	while (len--)
	{
		result[len] = base[v % b];
		v /= b;
	}
	result = utoa_puthash(result, hash, size, b);
	return (result);
}
