/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 23:39:30 by astepano          #+#    #+#             */
/*   Updated: 2017/03/11 23:41:30 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define K 6

static double	nth_root(double a, int n)
{
	int		k;
	double	x[K];

	x[0] = 1;
	k = 0;
	while (k < K - 1)
	{
		x[k + 1] = (1.0 / n) * ((n - 1) * x[k] + a / ft_pow(x[k], n - 1));
		k++;
	}
	return (x[K - 1]);
}

double			ft_pow(double base, double ex)
{
	double	half_pow;

	if (base == 0)
		return (0);
	if (ex == 0)
		return (1);
	else if (ex < 0)
		return (1 / ft_pow(base, -ex));
	else if (ex > 0 && ex < 1)
		return (nth_root(base, (int)(1 / ex)));
	else if ((int)ex % 2 == 0)
	{
		half_pow = ft_pow(base, ex / 2);
		return (half_pow * half_pow);
	}
	else
		return (base * ft_pow(base, ex - 1));
}
