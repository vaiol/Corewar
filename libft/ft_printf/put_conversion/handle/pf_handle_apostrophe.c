/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_handle_apostrophe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 19:53:40 by astepano          #+#    #+#             */
/*   Updated: 2017/06/20 16:21:11 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pf_handle.h"

static size_t	ft_nbrlen(char *nbr)
{
	size_t	len;

	len = 0;
	while (nbr[len] && (nbr[len] > '9' || nbr[len] < '0'))
		len++;
	return (ft_strlen(nbr + len));
}

static char		*apostrophe_result(int len, int slen, char *result, char *nbr)
{
	size_t	a;
	int		nlen;

	nlen = (int)ft_nbrlen(nbr);
	a = 0;
	while (slen >= 0 && ++a)
	{
		if (a && !(a % 4) && nlen > 0)
			result[slen--] = ',';
		else
		{
			result[slen--] = nbr[len--];
			nlen--;
		}
	}
	return (result);
}

char			*pf_handle_apostrophe(char *nbr)
{
	char	*result;
	int		len;
	int		slen;
	int		nlen;

	if (!nbr)
		return (NULL);
	nlen = (int)ft_nbrlen(nbr);
	len = (int)ft_strlen(nbr);
	slen = len + ((nlen - 1) / 3);
	result = (char *)malloc(sizeof(char) * (slen + 1));
	result[slen--] = '\0';
	len--;
	result = apostrophe_result(len, slen, result, nbr);
	free(nbr);
	return (result);
}
