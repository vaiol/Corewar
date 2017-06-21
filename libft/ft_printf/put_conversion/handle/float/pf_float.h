/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_float.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/20 16:20:05 by astepano          #+#    #+#             */
/*   Updated: 2017/06/20 16:23:23 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PF_FLOAT_H
# define PF_FLOAT_H

# include <limits.h>
# include <float.h>
# include <math.h>
# include "../pf_handle.h"

# define MAX(a,b) ((a)>(b) ? (a) : (b))
# define MIN(a,b) ((a)<(b) ? (a) : (b))
# define CONCAT2(y) 0x1p ## y
# define CONCAT(y) CONCAT2(y)

typedef struct	s_arrays
{
	char		*copy;
	uint32_t	*a;
	uint32_t	*d;
	uint32_t	*r;
	uint32_t	*z;
}				t_arrays;

typedef struct	s_indecies
{
	char		*prefix;
	int			pl;
	int			e;
	int			exp_size;
	int			i;
	int			j;
}				t_indecies;

typedef struct	s_bufs
{
	char		buf[9 + LDBL_MANT_DIG / 4];
	char		ebuf0[sizeof(int) * 3];
	char		*ebuf;
}				t_bufs;

void			pf_rounder(int p, int t, t_arrays *a, t_indecies *i);
char			*pf_round_hex_cut(char *nbr, t_conversion *c);
void			pf_handle_g(t_arrays *a, t_indecies *i, t_conversion *c);
void			pf_handle_f(t_arrays *a, int p, t_bufs *bufs, int hash);
void			pf_handle_e(t_arrays *a, char *es, t_bufs *bufs,
		t_conversion *c);
void			pf_out(char **sp, const char *s, size_t l);
void			pf_pad(char **sp, char c, int w, int l);
char			*pf_fmt_unsigned(uintmax_t x, char *s);
int				pf_infinite(long double nbr, int t, char *copy,
		t_indecies *i);
char			*pf_infin(long double nbr, t_conversion *c, int sign);
void			pf_parse_int(t_indecies *i, t_arrays *a);
void			pf_parse_fract(t_indecies *i, t_arrays *a, int t, int p);
void			pf_next_function(t_indecies *i, t_arrays *a, t_conversion *c);
long double		pf_frexpl(long double value, int *e);

#endif
