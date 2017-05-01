#include "pf_float.h"

static void	handle_f2(int *p, t_arrays *a, t_bufs *bufs)
{
	char	*s;

	s = pf_fmt_unsigned(*(a->d), bufs->buf + 9);
	while (s > bufs->buf)
		*--s = '0';
	pf_out(&(a->copy), s, (size_t) MIN(9, *p));
	a->d++;
	*p -= 9;
}

void		pf_handle_f(t_arrays *a, int p, t_bufs *bufs, int hash)
{
	char	*s;

	if (a->a > a->r)
		a->a = a->r;
	a->d = a->a;
	while (a->d <= a->r)
	{
		s = pf_fmt_unsigned(*(a->d), bufs->buf + 9);
		if (a->d != a->a)
		{
			while (s > bufs->buf)
				*--s = '0';
		}
		else if (s == bufs->buf + 9)
			*--s = '0';
		pf_out(&(a->copy), s, bufs->buf + 9 - s);
		a->d++;
	}
	if (p || hash)
		pf_out(&(a->copy), ".", 1);
	while (a->d < a->z && p > 0)
		handle_f2(&p, a, bufs);
	pf_pad(&(a->copy), '0', p + 9, 9);
}
