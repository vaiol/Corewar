/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_rounder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/20 16:20:52 by astepano          #+#    #+#             */
/*   Updated: 2017/06/20 16:20:54 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pf_float.h"

static void		round_sub(int e, int i, t_arrays *a)
{
	*(a->d) = *(a->d) + i;
	while (*(a->d) > 999999999)
	{
		*(a->d)-- = 0;
		(*(a->d))++;
	}
	if (a->d < a->a)
		a->a = a->d;
	i = 10;
	e = (int)(9 * (a->r - a->a));
	while ((int)*a->a >= i)
	{
		i *= 10;
		e++;
	}
}

static void		round_one(int i, t_arrays *a, uint32_t x, t_indecies *in)
{
	long double	round;
	long double	small;

	round = CONCAT(LDBL_MANT_DIG);
	if (*(a->d) / i & 1)
		round += 2;
	if ((int)x < i / 2)
		small = 0x0.8p0;
	else if ((int)x == i / 2 && a->d + 1 == a->z)
		small = 0x1.0p0;
	else
		small = 0x1.8p0;
	if (in->pl && *(in->prefix) == '-')
	{
		round *= -1;
		small *= -1;
	}
	*(a->d) -= x;
	if (round + small != round)
		round_sub(in->e, i, a);
}

void			pf_rounder(int p, int t, t_arrays *arrays, t_indecies *indecies)
{
	int			i;
	int			j;
	uint32_t	x;

	j = p - ((t | 32) != 'f') * indecies->e - ((t | 32) == 'g' && p);
	if (j < 9 * (arrays->z - arrays->r - 1))
	{
		arrays->d = arrays->r + 1 + (j + 9 * LDBL_MAX_EXP) / 9 - LDBL_MAX_EXP;
		j += 9 * LDBL_MAX_EXP;
		j %= 9;
		j++;
		i = 10;
		while (j < 9)
		{
			i *= 10;
			j++;
		}
		x = *(arrays->d) % i;
		if (x || arrays->d + 1 != arrays->z)
			round_one(i, arrays, x, indecies);
		if (arrays->z > arrays->d + 1)
			arrays->z = arrays->d + 1;
		while (!arrays->z[-1] && arrays->z > arrays->a)
			arrays->z--;
	}
}

static void		recur(char *nbr, int index, char *base)
{
	int	i;

	if (index < 0)
		return ;
	if (nbr[index] == '.')
	{
		recur(nbr, index - 1, base);
		return ;
	}
	if (nbr[index] == base[15])
	{
		nbr[index] = base[0];
		recur(nbr, index - 1, base);
		return ;
	}
	i = 0;
	while (base[i])
	{
		if (nbr[index] == base[i])
			break ;
		i++;
	}
	nbr[index] = base[i + 1];
}

/*
** with round:
**
** if (nbr[3] != '.')
**     c->precision += 3;
** else
**     c->precision += 4;
*/

char			*pf_round_hex_cut(char *nbr, t_conversion *c)
{
	int		i;
	char	*bassement;
	char	*result;

	if (c->type == 'X')
		bassement = "0123456789ABCDEF";
	else
		bassement = "0123456789abcdef";
	if (c->precision < 0)
		return (nbr);
	if (nbr[3] != '.')
		return (ft_strcut(nbr, c->precision + 3));
	c->precision += 4;
	i = 0;
	while (bassement[i])
	{
		if (nbr[c->precision] == bassement[i])
			break ;
		i++;
	}
	if (i > 8)
		recur(nbr, c->precision - 1, bassement);
	result = ft_strcut(nbr, c->precision);
	return (result);
}
