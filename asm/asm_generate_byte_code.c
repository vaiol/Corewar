/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_generate_byte_code.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 15:03:38 by astepano          #+#    #+#             */
/*   Updated: 2017/05/24 15:10:31 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	asm_write(t_file_struct *content, int fd)
{
	int i;

	i = 0;
	while (i < 4)
		write(fd, &content->magic[i++], 1);
	i = (int)ft_strlen(content->prog_name);
	write(fd, content->prog_name, (size_t)i);
	while (i < PROG_NAME_LENGTH + 4)
	{
		write(fd, "\0", 1);
		i++;
	}
	asm_get_magic(content, (unsigned int)content->count);
	i = 0;
	while (i < 4)
		write(fd, &content->magic[i++], 1);
	i = (int)ft_strlen(content->comment);
	write(fd, content->comment, (size_t)i);
	while (i < COMMENT_LENGTH + 4)
	{
		write(fd, "\0", 1);
		i++;
	}
	write(fd, content->coding_string, (unsigned)content->count);
}

static void	asm_generate_programm(t_file_struct *content)
{
	int i;

	asm_get_magic(content, COREWAR_EXEC_MAGIC);
	asm_generate_byte_ops(content);
	i = 0;
	content->coding_string = (unsigned char *)malloc(sizeof(unsigned char));
	content->count = 0;
	while (content->ops[i])
	{
		content->coding_string = asm_join(content->coding_string,
				content->ops[i]->coding_string,
				content->count,
				content->ops[i]->count);
		content->count += content->ops[i]->count;
		i++;
	}
}

void		asm_generate_byte_code(t_file_struct *content)
{
	int	fd;

	if (asm_validate_content(content))
	{
		fd = open(content->file_name, O_CREAT | O_WRONLY, 0666);
		if (fd < 0)
		{
			ft_printf(MSG_ERR_FILE, content->file_name);
			return ;
		}
		asm_generate_programm(content);
		asm_write(content, fd);
		ft_printf(MSG_COMPLETE, content->file_name);
	}
}
