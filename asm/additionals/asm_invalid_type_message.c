#include "../asm.h"

char		*asm_invalid_type_message(t_operation *op, int number)
{
	char	*type;
	int		count;
	char	*err;

	count = asm_is_arg(op->args[number]);
	type = "undefined";
	if (count == T_REG)
		type = "register";
	else if (count == T_DIR || count == T_LAB)
		type = "direct";
	else if (count == T_IND)
		type = "indirect";
	err = ft_strfjoin("Invalid parameter ", ft_itoa(number), SECOND);
	err = ft_strfjoin(err, " type ", FIRST);
	err = ft_strfjoin(err, type, FIRST);
	err = ft_strfjoin(err, " for instruction ", FIRST);
	err = ft_strfjoin(err, op->name, FIRST);
	return (err);
}

 int	asm_invalid_content(t_file_struct *content)
{
	char	*error;

	if (!content)
	{
		ft_printf("Syntax error!");
		return (0);
	}
	if (content->comment == NULL || content->prog_name == NULL)
	{
		ft_printf("Lexical error!");
		return (0);
	}
	if ((error = asm_validate_operations(content)))
	{
		ft_printf("%s\n", error);
		free(error);
		return (0);
	}
	return (1);
}

