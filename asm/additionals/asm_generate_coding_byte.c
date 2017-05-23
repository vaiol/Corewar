#include "../asm.h"

unsigned char	asm_generate_codind_byte(t_operation *op)
{
	char bytes[8];
	int i;
	int arg;
	int count;

	i = 0;
	while (i < 8)
		bytes[i++] = '0';
	i = 0;
	count = 0;
	while (op->args[i])
	{
		arg = asm_is_arg(op->args[i]);
		if (arg == T_REG || arg == T_IND || (arg == T_LAB && op->args[i][0] != DIRECT_CHAR))
			bytes[count + 1] = '1';
		if (arg == T_DIR || arg == T_LAB || arg == T_IND)
			bytes[count] = '1';
		count += 2;
		i++;
	}
	return ((unsigned char)(ft_atoi_base(bytes, 2)));
}

