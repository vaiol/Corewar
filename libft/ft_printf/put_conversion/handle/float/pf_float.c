#include "pf_float.h"

static void	pre_parse(long double *nbr, t_arrays *a)
{
	int i;

	i = 1;
	while (i || *nbr)
	{
		*(a->z) = (uint32_t)*nbr;
		*nbr = 1000000000 * ((*nbr) - *(a->z)++);
		i = 0;
	}
}

static void	post_parse(t_arrays *a, t_indecies *i)
{
	if (a->a < a->z)
	{
		i->i = 10;
		i->e = (int)(9 * (a->r - a->a));
		while ((int)*a->a >= i->i)
		{
			i->i *= 10;
			i->e++;
		}
	}
	else
		i->e = 0;
}

static int	init(long double *nbr, t_arrays *a, int t, t_indecies **i)
{
	(*i) = (t_indecies *)malloc(sizeof(t_indecies));
	(*i)->prefix = "-0X+0X 0X-0x+0x 0x";
	(*i)->exp_size = 0;
	(*i)->pl = 1;
	if ((*nbr) < 0 || 1 / (*nbr) < 0)
		(*nbr) = -(*nbr);
	else
	{
		(*i)->prefix++;
		(*i)->pl = 0;
	}
	if (pf_infinite(*nbr, t, a->copy, *i))
		return (1);
	(*nbr) = pf_frexpl(*nbr, &((*i)->exp_size)) * 2;
	if (*nbr)
	{
		(*i)->exp_size--;
		(*nbr) *= 0x1p28;
		(*i)->exp_size -= 28;
	}
	return (0);
}

void		pf_ftoa_conv(char *outstr, long double nbr, t_conversion *c)
{
	uint32_t	b[(LDBL_MAX_EXP + LDBL_MANT_DIG) / 9 + 1];
	t_arrays	*a;
	t_indecies	*indecies;
	uint32_t	*bi;

	a = (t_arrays *)malloc(sizeof(t_arrays));
	a->copy = outstr;
	if (init(&nbr, a, c->type, &indecies))
		return ;
	if (indecies->exp_size < 0)
		bi = b;
	else
		bi = b + sizeof(b) / sizeof(*b) - LDBL_MANT_DIG - 1;
	c->precision = c->precision < 0 ? 6 : c->precision;
	a->a = bi;
	a->r = bi;
	a->z = bi;
	pre_parse(&nbr, a);
	pf_parse_int(indecies, a);
	pf_parse_fract(indecies, a, c->type, c->precision);
	post_parse(a, indecies);
	pf_rounder(c->precision, c->type, a, indecies);
	if ((c->type | 32) == 'g')
		pf_handle_g(a, indecies, c);
	pf_next_function(indecies, a, c);
}

void		pf_next_function(t_indecies *i, t_arrays *a, t_conversion *c)
{
	t_bufs		*bufs;
	char		*estr;
	uintmax_t	ie;

	estr = NULL;
	bufs = (t_bufs *)malloc(sizeof(t_bufs));
	bufs->ebuf = &(bufs->ebuf0[sizeof(int) * 3]);
	if ((c->type | 32) != 'f')
	{
		ie = i->e < 0 ? (uintmax_t)-(i->e) : (uintmax_t)i->e;
		estr = pf_fmt_unsigned(ie, bufs->ebuf);
		while (bufs->ebuf - estr < 2)
			*(--estr) = '0';
		*(--estr) = (char)(i->e < 0 ? '-' : '+');
		*(--estr) = (char)c->type;
	}
	pf_out(&(a->copy), i->prefix, (size_t) i->pl);
	if ((c->type | 32) == 'f')
		pf_handle_f(a, c->precision, bufs, c->hashtag);
	else
		pf_handle_e(a, estr, bufs, c);
	*(a->copy) = 0;
}
