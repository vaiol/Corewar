/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readfd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 14:11:37 by astepano          #+#    #+#             */
/*   Updated: 2017/04/01 14:11:39 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_readfd(int fd)
{
	ssize_t	size;
	char	buffer[BUFF_SIZE + 1];
	char	*result;

	result = NULL;
	while ((size = read(fd, buffer, BUFF_SIZE)))
	{
		buffer[size] = '\0';
		if (result == NULL)
			result = ft_strdup("");
		result = ft_strfjoin(result, buffer, FIRST);
	}
	return (result);
}
