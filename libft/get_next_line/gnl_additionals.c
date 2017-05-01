/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_additionals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 23:16:19 by astepano          #+#    #+#             */
/*   Updated: 2017/03/21 23:16:24 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*split_line(char **str)
{
	char	*input;
	char	*result;
	int		len;

	input = *str;
	if (!input)
		return (NULL);
	len = ft_strichr(input, '\n');
	if (len < 0)
		return (NULL);
	result = ft_strsub(input, 0, (size_t)len);
	if (input[len + 1] == '\0')
		*str = NULL;
	else
		*str = ft_strsub(input, (unsigned)len + 1, ft_strlen(input) - len - 1);
	free(input);
	return (result);
}

static char	*readstr(int fd)
{
	ssize_t	size;
	char	buffer[BUFF_SIZE + 1];

	if ((size = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[size] = '\0';
		return (ft_strdup(buffer));
	}
	else
		return (NULL);
}

static void	cleanfd(t_lines **begin, int fd)
{
	t_lines	*node;
	t_lines	*prev;

	if ((*begin) == NULL)
		return ;
	node = *begin;
	if ((*begin)->fd == fd)
	{
		*begin = (*begin)->next;
		free(node->content);
		free(node);
		return ;
	}
	while (node && node->fd != fd)
	{
		prev = node;
		node = node->next;
	}
	if (node == NULL)
		return ;
	prev->next = node->next;
	free(node->content);
	free(node);
}

int			gnl_createfd(t_lines **begin, int fd)
{
	t_lines	*new_node;
	t_lines	*node;
	char	*str;

	node = *begin;
	while (node && node->fd != fd)
		node = node->next;
	if (node != NULL)
		return (1);
	if ((str = readstr(fd)) == NULL)
		return (0);
	new_node = (t_lines *)malloc(sizeof(t_lines));
	new_node->fd = fd;
	new_node->next = NULL;
	new_node->content = str;
	if ((*begin) == NULL)
	{
		*begin = new_node;
		return (1);
	}
	node = *begin;
	while (node->next)
		node = node->next;
	node->next = new_node;
	return (1);
}

char		*gnl_get_line(int fd, t_lines **begin)
{
	char	*result;
	char	*buff;
	t_lines	*node;

	node = *begin;
	while (node && node->fd != fd)
		node = node->next;
	while ((result = split_line(&(node->content))) == NULL)
	{
		if ((buff = readstr(fd)) == NULL)
		{
			if (!node->content)
				return (NULL);
			buff = ft_strdup(node->content);
			cleanfd(begin, fd);
			return (buff);
		}
		if (!node->content)
			node->content = buff;
		else
			node->content = ft_strfjoin(node->content, buff, BOTH);
	}
	return (result);
}
