#include "corewar.h"

void	count_files(t_data *data, char **argv)
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

int		get_magic(unsigned char *str)
{
	int magic;

	magic = str[0] << 24;
	magic += str[1] << 16;
	magic += str[2] << 8;
	magic += str[3];
	return (magic);
}

char	*to_two_base(unsigned char c)
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

// 					hex to decimal function

//int hex_to_dec(int nbr) // recursive fn
//{
//	int nConverted = 0; // Clear this for calculation
//	int nQuotient;
//	int nRemainder;
//
//	nQuotient = (nbr / 16);
//	nRemainder = (nbr % 16);
//
//	if ( nQuotient == 0)
//		nConverted = nRemainder;
//	else
//		nConverted = (16 * hex_to_dec(nQuotient) + nRemainder);
//	return (nConverted);
//}

// 					max 4 char to int function

//int		uchar_to_int(unsigned char *str)
//{
//	int integer;
//
////	integer = str[0] << 24;
////	integer += str[1] << 16;
////	integer += str[2] << 8;
////	integer += str[3];
////	integer = str[0] << 24;
////	integer += str[1] << 16;
////	integer += 0 << 8;
////	integer += 0;
//
//	integer = 0 << 24;
//	integer += 0 << 16;
//	integer += str[0] << 8;
//	integer += str[1];
//
//
////	integer = str[0] << 8;
////	integer += str[1];
//	return (integer);
//}