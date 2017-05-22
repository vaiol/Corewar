#include "../asm.h"

int		asm_skip_empty_lines(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t'
		   || str[i] == '\n' || str[i] == '\v'
		   || str[i] == '\f' || str[i] == '\r')
		i++;
	return (i);
}

int		asm_skip_spaces(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
		   || str[i] == '\f' || str[i] == '\r')
		i++;
	return (i);
}