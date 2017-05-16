#include "asm.h"

t_op    op_tab[OP_COUNT] =
{
		{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
		{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
		{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
		{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
		{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
		{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
				"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
		{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
				"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
		{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
				"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
		{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
		{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
				"load index", 1, 1},
		{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
				"store index", 1, 1},
		{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
		{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
		{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
				"long load index", 1, 1},
		{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
		{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
		{0, 0, {0}, 0, 0, 0, 0, 0}
};

void	get_index(t_operation *op)
{
	int	i;

	i = 0;
	while (i < OP_COUNT)
	{
		if (ft_strequ(op->name, op_tab[i].name))
		{
			op->index = i;
			break ;
		}
		i++;
	}
}

int		validate_count_args(t_operation *op)
{
	int	count;

	count = 0;
	while (op->args[count])
		count++;
	if (count != op_tab[op->index].count_args)
		return (0);
	return (1);
}

int		label_exist(t_file_struct *content, char *label)
{
	int	i;

	i = 0;
	while (content->ops[i])
	{
		if (ft_strequ(content->ops[i]->label, label))
			return (1);
		i++;
	}
	return (0);
}

int		wrong_arg_type(t_operation *op, int i, int arg)
{
	int	type;

	if (arg == T_LAB)
		arg = T_DIR;
	type = op_tab[op->index].args[i];
	if (arg == T_REG)
	{
		if (type == T_DIR || type == T_IND ||  type == (T_DIR | T_IND))
			return (1);
	}
	else if (arg == T_DIR)
	{
		if (type == T_REG || type == T_IND ||  type == (T_REG | T_IND))
			return (1);
	}
	else if (arg == T_IND)
	{
		if (type == T_DIR || type == T_REG ||  type == (T_DIR | T_REG))
			return (1);
	}
	return (0);
}

int		validate_args(t_file_struct *content, t_operation *op)
{
	int	arg;
	int	i;

	i = 0;
	while (op->args[i])
	{
		arg = asm_is_arg(op->args[i]);
		if (arg < 0)
			return (0);
		if (arg == 8 && !label_exist(content, op->args[i] + 2))
			return (0);
		if (wrong_arg_type(op, i, arg))
			return (0);
		i++;
	}
	return (1);
}

int		asm_validate_operations(t_file_struct *content)
{
	int	i;

	i = 0;
	while (content->ops[i])
	{
		get_index(content->ops[i]);
		if (content->ops[i]->index == -1)
			return (0);
		if (!validate_count_args(content->ops[i]))
			return (0);
		if (!validate_args(content, content->ops[i]))
			return (0);
		i++;
	}
	return (1);
}
