/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_generate_byte_operations.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:37:02 by astepano          #+#    #+#             */
/*   Updated: 2017/05/24 14:38:04 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	get_dir_value(t_file_struct *f, int c, int a, int index)
{
	unsigned int n;

	if (asm_is_arg(f->ops[index]->args[a]) == T_LAB)
		n = (unsigned int)asm_label_len(f, f->ops[index]->args[a] + 2, index);
	else
		n = (unsigned int)ft_atoi(f->ops[index]->args[a] + 1);
	if (g_op_tab[f->ops[index]->index].label_size)
		n = (unsigned short)n;
	if (!g_op_tab[f->ops[index]->index].label_size)
	{
		f->ops[index]->coding_string[c++] = (unsigned char)((n >> 24) & 0xFF);
		f->ops[index]->coding_string[c++] = (unsigned char)((n >> 16) & 0xFF);
	}
	f->ops[index]->coding_string[c++] = (unsigned char)((n >> 8) & 0xFF);
	f->ops[index]->coding_string[c++] = (unsigned char)(n & 0xFF);
	return (c);
}

static int	get_indir_value(t_file_struct *f, int count, int a, int index)
{
	unsigned short n;

	if (asm_is_arg(f->ops[index]->args[a]) == T_LAB)
		n = (unsigned short)asm_label_len(f, f->ops[index]->args[a] + 1, index);
	else
		n = (unsigned short)ft_atoi(f->ops[index]->args[a]);
	f->ops[index]->coding_string[count++] = (unsigned char)((n >> 8) & 0xFF);
	f->ops[index]->coding_string[count++] = (unsigned char)(n & 0xFF);
	return (count);
}

static void	generate_byte_argument(t_file_struct *f, int c, int index)
{
	int i;
	int arg;

	i = 0;
	while (f->ops[index]->args[i])
	{
		arg = asm_is_arg(f->ops[index]->args[i]);
		if (arg == T_REG)
			f->ops[index]->coding_string[c++] = (unsigned char)ft_atoi(
					f->ops[index]->args[i] + 1);
		else if (arg == T_IND || (arg == T_LAB
					&& f->ops[index]->args[i][0] != DIRECT_CHAR))
			c = get_indir_value(f, c, i, index);
		else if (arg == T_DIR || arg == T_LAB)
			c = get_dir_value(f, c, i, index);
		i++;
	}
	f->ops[index]->count = c;
}

static int	generate_codind_byte(t_operation *op)
{
	char	bytes[9];
	int		i;
	int		arg;
	int		count;

	i = 0;
	while (i < 8)
		bytes[i++] = '0';
	bytes[8] = '\0';
	i = 0;
	count = 0;
	while (op->args[i])
	{
		arg = asm_is_arg(op->args[i]);
		if (arg == T_REG || arg == T_IND
			|| (arg == T_LAB && op->args[i][0] != DIRECT_CHAR))
			bytes[count + 1] = '1';
		if (arg == T_DIR || arg == T_LAB || arg == T_IND)
			bytes[count] = '1';
		count += 2;
		i++;
	}
	return ((unsigned char)ft_atoi_base(bytes, 2));
}

void		asm_generate_byte_ops(t_file_struct *f)
{
	int i;
	int c;

	asm_get_prog_len(f);
	i = 0;
	while (f->ops[i] && !f->ops[i]->eof)
	{
		c = 0;
		f->ops[i]->coding_string[c++] = (unsigned char)
				g_op_tab[f->ops[i]->index].opcode;
		if (g_op_tab[f->ops[i]->index].octal_coding)
			f->ops[i]->coding_string[c++] = (unsigned char)generate_codind_byte(
					f->ops[i]);
		generate_byte_argument(f, c, i);
		i++;
	}
}
