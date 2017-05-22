#include "asm.h"

 int 	get_dir_value(t_file_struct *content, int count, int arg, int index)
{
	unsigned int n;

	if (asm_is_arg(content->ops[index]->args[arg]) == T_LAB)
		n = (unsigned int)get_label_len(content, content->ops[index]->args[arg] + 2, index);
	else
		n = (unsigned int)ft_atoi(content->ops[index]->args[arg] + 1);
	if (g_op_tab[content->ops[index]->index].label_size)
		n = (unsigned short)n;
	if (!g_op_tab[content->ops[index]->index].label_size)
	{
		content->ops[index]->coding_string[count++] = (unsigned char)((n >> 24) & 0xFF);
		content->ops[index]->coding_string[count++] = (unsigned char)((n >> 16) & 0xFF);
	}
	content->ops[index]->coding_string[count++] = (unsigned char)((n >> 8) & 0xFF);
	content->ops[index]->coding_string[count++] = (unsigned char)(n & 0xFF);
	return (count);
}

int 	get_indir_value(t_file_struct *content, int count, int arg, int index)
{
	unsigned short n;

	if (asm_is_arg(content->ops[index]->args[arg]) == T_LAB)
		n = (unsigned short)get_label_len(content, content->ops[index]->args[arg] + 1, index);
	else
		n = (unsigned short)ft_atoi(content->ops[index]->args[arg]);
	content->ops[index]->coding_string[count++] = (unsigned char)((n >> 8) & 0xFF);
	content->ops[index]->coding_string[count++] = (unsigned char)(n & 0xFF);
	return (count);
}

void		asm_generate_coding_argument(t_file_struct *content, int count, int index)
{
	int i;
	int arg;

	i = 0;
	while (content->ops[index]->args[i])
	{
		arg = asm_is_arg(content->ops[index]->args[i]);
		if (arg == T_REG)
			content->ops[index]->coding_string[count++] = (unsigned char)ft_atoi(content->ops[index]->args[i] + 1);
		else if (arg == T_IND || (arg == T_LAB && content->ops[index]->args[i][0] != DIRECT_CHAR))
			count = get_indir_value(content, count, i, index);
		else if (arg == T_DIR || arg == T_LAB)
			count = get_dir_value(content, count, i, index);
		i++;
	}
	content->ops[index]->count = count;
}
void		get_ops_len(t_file_struct *content)
{
	int	i;
	int	j;
	int	arg;

	i = 0;
	while (content->ops[i])
	{
		content->ops[i]->len = 1;
		if (g_op_tab[content->ops[i]->index].octal_coding)
			content->ops[i]->len++;
		j = 0;
		while (content->ops[i]->args[j])
		{
			arg = asm_is_arg(content->ops[i]->args[j]);
			if (arg == T_REG)
				content->ops[i]->len++;
			else if (arg == T_IND || (arg == T_LAB && content->ops[i]->args[j][0] != DIRECT_CHAR))
				content->ops[i]->len += 2;
			else if (arg == T_DIR || arg == T_LAB)
			{
				if (!g_op_tab[content->ops[i]->index].label_size)
					content->ops[i]->len += 2;
				content->ops[i]->len += 2;
			}
			j++;
		}
		i++;
	}
}
void		asm_generate_coding_comand(t_file_struct *content)
{
	int i;
	int coding;

	get_ops_len(content);
	i = 0;
	while (content->ops[i])
	{
		coding = 0;
		content->ops[i]->coding_string[coding++] = (unsigned char)g_op_tab[content->ops[i]->index].opcode;
		if (g_op_tab[content->ops[i]->index].octal_coding)
			content->ops[i]->coding_string[coding++] = asm_generate_codind_byte(content->ops[i]);
		asm_generate_coding_argument(content, coding, i);
		i++;
	}
	asm_generate_programm(content);
}
