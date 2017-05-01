/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_winttostr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 19:26:22 by astepano          #+#    #+#             */
/*   Updated: 2017/04/02 19:26:23 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pf_util.h"

static char	*createwint(wint_t wint, int len)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (len + 1));
	str[len--] = '\0';
	if (len == 0)
	{
		str[len] = (char)wint;
		return (str);
	}
	str[len--] = (char)((wint & 63) + 128);
	if (len == 0)
	{
		str[len] = (char)(((wint & 1984) >> 6) + 192);
		return (str);
	}
	str[len--] = (char)(((wint & 4032) >> 6) + 128);
	if (len == 0)
	{
		str[len] = (char)(((wint & 61440) >> 12) + 224);
		return (str);
	}
	str[len--] = (char)(((wint & 258048) >> 12) + 128);
	str[len] = (char)(((wint & 1835008) >> 18) + 240);
	return (str);
}

char		*pf_winttostr(wint_t wint)
{
	if (wint < 128)
		return (createwint(wint, 1));
	if (wint < 2048)
		return (createwint(wint, 2));
	if (wint < 65536)
		return (createwint(wint, 3));
	if (wint < 1114112)
		return (createwint(wint, 4));
	return (NULL);
}
