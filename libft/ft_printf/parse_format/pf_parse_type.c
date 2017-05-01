/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 19:31:12 by astepano          #+#    #+#             */
/*   Updated: 2017/04/02 19:31:14 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pf_parse_all.h"

size_t		pf_parse_type(const char *f, size_t i, t_conversion *form)
{
	if (ft_strcchr("SDOUC", f[i]))
	{
		form->size = L;
		form->type = (char)ft_tolower(f[i]);
	}
	else
		form->type = f[i];
	return (i + 1);
}
