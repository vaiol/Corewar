/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 21:06:02 by astepano          #+#    #+#             */
/*   Updated: 2017/03/04 21:06:03 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcut(char *str, int max_len)
{
	char	*result;
	int		str_len;
	int		i;

	if (max_len < 0)
		return (str);
	str_len = (int)ft_strlen(str);
	if (str_len < max_len)
		max_len = (int)str_len;
	result = (char *)malloc(sizeof(char) * (max_len + 1));
	i = 0;
	while (i < max_len)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	free(str);
	return (result);
}
