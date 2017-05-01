#include "pf_float.h"

static void	handle_g2(t_indecies *i, t_conversion *c, t_arrays *a)
{
	long	max;

	if (a->z > a->a && a->z[-1])
	{
		i->i = 10;
		i->j = 0;
		while ((a->z[-1] % i->i) == 0)
		{
			i->i *= 10;
			i->j++;
		}
	}
	else
		i->j = 9;
	max = 9 * (a->z - a->r - 1);
	if ((c->type | 32) == 'f')
		c->precision = MIN(c->precision, MAX(0, max - i->j));
	else
		c->precision = MIN(c->precision, MAX(0, max + i->e - i->j));
}

void		pf_handle_g(t_arrays *a, t_indecies *i, t_conversion *c)
{
	if (!c->precision)
		c->precision++;
	if (c->precision > i->e && i->e >= -4)
	{
		c->type--;
		c->precision -= i->e + 1;
	}
	else
	{
		c->type -= 2;
		c->precision--;
	}
	if (!c->hashtag)
		handle_g2(i, c, a);
}
