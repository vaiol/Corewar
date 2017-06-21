/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_handle_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/20 16:20:15 by astepano          #+#    #+#             */
/*   Updated: 2017/06/20 16:20:16 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pf_float.h"

static unsigned long	ftohex(long double f, unsigned b, unsigned eb, int *e)
{
	long double			fnorm;
	int					shift;
	unsigned long long	sgn;
	unsigned			signbits;

	signbits = b - eb - 1;
	if (f == 0.0)
		return ((unsigned)(*e = 0));
	fnorm = f;
	shift = 0;
	while (fnorm >= 2.0)
	{
		fnorm /= 2.0;
		shift++;
	}
	while (fnorm < 1.0)
	{
		fnorm *= 2.0;
		shift--;
	}
	fnorm = fnorm - 1.0;
	sgn = (unsigned long long)(fnorm * ((1LL << signbits) + 0.5f));
	*e = shift;
	return (((long long)(1 + ((1 << (eb)) - 1)) << (b - eb - 1)) | sgn);
}

static char				*get_exponent(int e, t_conversion *c)
{
	char	*result;
	char	*postfix;

	postfix = (c->type == 'x') ? "p" : "P";
	result = ft_itoa_base(e, 10);
	if (result[0] != '-')
		result = ft_strfjoin("+", result, SECOND);
	result = ft_strfjoin(postfix, result, SECOND);
	return (result);
}

static char				*get_pf(unsigned long long n, t_conversion *c, char *s)
{
	char	*prefix;

	prefix = (n == 0) ? "0" : "1";
	if (c->precision > 0 || (s[0] && c->precision))
		prefix = ft_strjoin(prefix, ".");
	if (c->type == 'x')
		prefix = ft_strjoin("0x", prefix);
	else
		prefix = ft_strjoin("0X", prefix);
	return (prefix);
}

static char				*get_value(unsigned long long hex, t_conversion *c)
{
	int		len;
	char	*str;
	char	*tmp;

	str = pf_utoa_base(hex, 16, (char)c->type, 0);
	tmp = str;
	str = ft_strdup(str + 3);
	free(tmp);
	str = pf_zerocut(str);
	len = (int)ft_strlen(str);
	str = ft_strfjoin(get_pf(hex, c, str), str, SECOND);
	if (c->precision > len)
		str = pf_strjoinchr(str, '0', c->precision - len, END);
	else if (c->precision < len)
		str = pf_round_hex_cut(str, c);
	return (str);
}

char					*pf_handle_a(long double nbr, t_conversion *c)
{
	unsigned long long	hex;
	int					sign;
	char				*str;
	int					e;

	sign = 0;
	c->type += ('x' - 'a');
	if (nbr < 0 || (1 / nbr) < 0)
	{
		nbr = -nbr;
		sign = 1;
	}
	if (nbr == INFINITY || nbr != nbr)
		return (pf_infin(nbr, c, sign));
	if (nbr == 0.0 && c->precision < 0)
		c->precision = 0;
	hex = ftohex(nbr, 64, 11, &e);
	str = get_value(hex, c);
	str = ft_strfjoin(str, get_exponent(e, c), BOTH);
	if (sign)
		str = ft_strfjoin("-", str, SECOND);
	c->type -= ('x' - 'a');
	return (str);
}
