#include "../asm.h"

char *asm_generate_string(char **file)
{
	char *str;
	int i;

	i = 0;
	str = ft_strdup("");
	while (file && file[i])
	{
		str = ft_strfjoin(str, file[i], BOTH);
		i++;
	}
	free(file);
	return (str);
}
