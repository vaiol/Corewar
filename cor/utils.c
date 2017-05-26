#include "corewar.h"

void		count_files(t_data *data, char **argv)
{
	int i;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] != '-')
			data->count++;
		i++;
	}
	if (data->count > 4)
		error_handler("Error : To much players");
}

int			char_to_int(unsigned char *str)
{
	int nbr;

	nbr = str[0] << 24;
	nbr += str[1] << 16;
	nbr += str[2] << 8;
	nbr += str[3];
	return (nbr);
}

char		*to_two_base(unsigned char c)
{
	int		i;
	int		j;
	char	*binary;

	binary = ft_strnew(7);
	i = 7;
	j = 0;
	while (i >= 0)
	{
		if (c & (1 << i))
			binary[j] = '1';
		else
			binary[j] = '0';
		--i;
		j++;
	}
	return (binary);
}

unsigned char	*int_to_str(int n)
{
//	unsigned char	str[4];

	unsigned char	*str;

	str = (unsigned char *)malloc(sizeof(char) * 4);

	str[0] = (n >> 24) & 0xFF;
	str[1] = (n >> 16) & 0xFF;
	str[2] = (n >> 8) & 0xFF;
	str[3] = n & 0xFF;
	return (str);
}