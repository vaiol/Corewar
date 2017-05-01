/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_put_unprintable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 19:48:19 by astepano          #+#    #+#             */
/*   Updated: 2017/04/02 19:48:20 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pf_put_conversion.h"

static char	*add_str(char *s1, size_t index, char *s2)
{
	char	*result;
	int		i;
	int		j;

	result = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	i = -1;
	j = 0;
	while (++i < (int)index)
		result[i] = s1[i];
	while (s2[j])
	{
		result[i + j] = s2[j];
		j++;
	}
	j = i + j;
	i++;
	while (s1[i])
	{
		result[j] = s1[i];
		i++;
		j++;
	}
	result[j] = '\0';
	return (result);
}

static char	*add_unprintable(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (ft_isprint(str[i]))
		{
			i++;
			continue ;
		}
		else if (str[i] == '\t')
			str = add_str(str, i, "\\t");
		else if (str[i] == '\n')
			str = add_str(str, i, "\\n");
		else if (str[i] == '\v')
			str = add_str(str, i, "\\v");
		else if (str[i] == '\f')
			str = add_str(str, i, "\\f");
		else if (str[i] == '\r')
			str = add_str(str, i, "\\r");
		else
			str = add_str(str, i, pf_utoa_base((unsigned)str[i], 16, 'x', 1));
		i = 0;
	}
	return (str);
}

void		pf_put_unprintable(t_conversion *conv, va_list valist)
{
	char	*str;

	str = ft_strdup(va_arg(valist, char *));
	str = add_unprintable(str);
	str = ft_strcut(str, conv->precision);
	conv->precision = -1;
	str = pf_handle_minwidth(conv, str, 0);
	pf_putstr(str);
	free(str);
}
