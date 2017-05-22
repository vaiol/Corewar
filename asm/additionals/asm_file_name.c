#include "../asm.h"

char 		*asm_file_name(char *str, char *file_name)
{
	unsigned int i;
	unsigned int flag;

	i = 0;
	flag = 0;
	while(file_name[i])
	{
		if(file_name[i] == '/')
			flag = ++i;
		i++;
	}
	str = ft_strsub(file_name, flag, ft_strlen(file_name + flag) - 2);
	str = ft_strfjoin(str, ".cor", FIRST);
	return (str);
}