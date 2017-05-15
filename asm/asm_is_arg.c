#include "asm.h"

static int is_register(char *arg)
{
	if(arg[0] != 'r' || !ft_isdigit(arg[1]))
		return (0);
	if(!arg[2])
		return (1);
	if(!ft_isdigit(arg[2]) || arg[3])
		return (0);
	return (1);
}

static int is_direction(char *arg)
{
	int i;

	if(arg[0] != DIRECT_CHAR)
		return (0);
	i = 1;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static int		is_indirection(char *arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static int		is_label(char *arg)
{
	int i;

	if(arg[0] != DIRECT_CHAR || arg[1] != LABEL_CHAR)
		return (0);
	i = 2;
	while (arg[i] && ft_strchr(LABEL_CHARS, arg[i]))
		i++;
	if (arg[i] != '\0')
		return (0);
	return (1);
}



int				asm_is_arg(char *arg)
{
	if (is_register(arg))
		return (T_REG);
	if (is_direction(arg))
		return (T_DIR);
	if (is_indirection(arg))
		return (T_IND);
	if (is_label(arg))
		return (T_LAB);
	return (-1);
}

