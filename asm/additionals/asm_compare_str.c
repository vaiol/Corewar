#include "../asm.h"

int		asm_compare_str(char *str, char *str2)
{
	int	i;
	int	j;

	i = asm_skip_spaces(str, 0);
	j = 0;
	while (str[i] == str2[j])
	{
		i++;
		j++;
	}
	if (str2[j])
		return (0);
	return (i);
}
