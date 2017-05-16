#include "corewar.h"

int		uchar_to_int(unsigned char *str)
{
	int integer;

//	integer = str[0] << 24;
//	integer += str[1] << 16;
//	integer += str[2] << 8;
//	integer += str[3];
//	integer = str[0] << 24;
//	integer += str[1] << 16;
//	integer += 0 << 8;
//	integer += 0;

	integer = 0 << 24;
	integer += 0 << 16;
	integer += str[0] << 8;
	integer += str[1];


//	integer = str[0] << 8;
//	integer += str[1];
	return (integer);
}

void	print_map(int *map)
{
	int i;
	int y;

	i = 0;
	y = 1;
	while (i < MEM_SIZE)
	{
//		ft_printf("%02s ",ft_itoa_base(map[i], 16));
		ft_printf("%02x ",map[i]);
//		ft_printf("%i ", map[i]);
		if (y >= 100)
		{
			ft_printf("\n");
			y = 0;
		}
		y++;
		i++;
	}
};

//
int HexToDec(int nNumToConvert) // recursive fn
{
	int nConverted = 0; // Clear this for calculation
	int nQuotient;
	int nRemainder;

	nQuotient = (nNumToConvert / 16);
	nRemainder = (nNumToConvert % 16);

	if ( nQuotient == 0)
	{
		nConverted = nRemainder;
	}
	else
	{
		nConverted = (16 * HexToDec(nQuotient) + nRemainder);
	}
	return (nConverted);
}

void	fill_map(t_data *data, t_champ *champ)
{
	unsigned char hex[2];
	unsigned int i;
	int pos;

	int to_int;

	i = 0;
	pos = champ->start_pos;

	while (i < champ->prog_size)
	{
		hex[0] = champ->program[i];
		i++;
		hex[1] = champ->program[i];
//		hex[2] = '\0';



		to_int = uchar_to_int(hex);

//		ft_printf("hex = %x\n", HexToDec(to_int));

//		ft_printf("uint = %u\n \n", to_int);


//		to_int = HexToDec(champ->program[i]);
		data->map[i + pos] = to_int;

//		ft_printf("sp = %i\n", i + pos);
//
//		ft_printf("map = %i\n", data->map[i + pos]);

//		data->map[i + pos] = champ->program[i];
		i++;
	}

}

void	prefill_map(t_data *data)
{
	int i;
	int n;

	i = 0;
	while (i < MEM_SIZE)
	{
		data->map[i] = 0;
		i++;
	}

	n = 0;
	while (n < data->count)
	{
		fill_map(data, &data->champs[n]);
		n++;
	}

	print_map(data->map);

//	ft_print_memory(data->map, MEM_SIZE + 1);
}
