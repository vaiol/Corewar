/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_brace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 19:30:37 by astepano          #+#    #+#             */
/*   Updated: 2017/04/02 19:30:38 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pf_parse_all.h"

static char		**create_colors(void)
{
	char	**array;

	array = (char **)malloc(sizeof(char *) * 10);
	array[0] = "black}";
	array[1] = "red}";
	array[2] = "green}";
	array[3] = "yellow}";
	array[4] = "blue}";
	array[5] = "magenta}";
	array[6] = "cyan}";
	array[7] = "white}";
	array[8] = "eoc}";
	array[9] = NULL;
	return (array);
}

static char		**create_escapes(void)
{
	char	**array;

	array = (char **)malloc(sizeof(char *) * 10);
	array[0] = "\x1B[30m\0";
	array[1] = "\x1B[31m\0";
	array[2] = "\x1B[32m\0";
	array[3] = "\x1B[33m\0";
	array[4] = "\x1B[34m\0";
	array[5] = "\x1B[35m\0";
	array[6] = "\x1B[36m\0";
	array[7] = "\x1B[37m\0";
	array[8] = "\x1B[0m\0";
	array[9] = NULL;
	return (array);
}

static size_t	equal(char *str, char *format)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ft_tolower(format[i]))
			return (0);
		i++;
	}
	return (i);
}

static size_t	setfd(char *format, size_t i, va_list valist)
{
	size_t	len;

	if ((len = equal("fd}", format)))
	{
		g_fd = va_arg(valist, int);
		return (i + len);
	}
	return (i);
}

size_t			pf_parse_brace(const char *f, size_t i, va_list valist)
{
	char	*format;
	char	**colors;
	char	**escapes;
	size_t	len;
	size_t	index;

	format = (char *)f + i;
	if ((len = setfd(format, i, valist)) != i)
		return (len);
	colors = create_colors();
	escapes = create_escapes();
	index = 0;
	while (colors[index])
	{
		if ((len = equal(colors[index], format)))
		{
			pf_putstr(escapes[index]);
			return (pf_free_brace(colors, escapes, i + len));
		}
		index++;
	}
	pf_putstr("{");
	return (pf_free_brace(colors, escapes, i));
}
