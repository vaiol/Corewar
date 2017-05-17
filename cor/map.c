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

void	print_map(t_data *data)
{
	int i;
	int x;

	i = 0;
	x = 1;
	while (i < MEM_SIZE)
	{
		ft_printf("%02x ",data->map[i]);

		if (x >= 64)
		{
			ft_printf("\n");
			x = 0;
		}
		x++;
		i++;
	}
};


int hex_to_dec(int nbr) // recursive fn
{
	int nConverted = 0; // Clear this for calculation
	int nQuotient;
	int nRemainder;

	nQuotient = (nbr / 16);
	nRemainder = (nbr % 16);

	if ( nQuotient == 0)
		nConverted = nRemainder;
	else
		nConverted = (16 * hex_to_dec(nQuotient) + nRemainder);
	return (nConverted);
}

void	fill_map(t_data *data, t_champ *champ)
{

	int				pos;
	unsigned int	i;

	pos = champ->start_pos;

	i = 0;
	while (i < champ->prog_size)
	{
		data->map[i + pos] = champ->program[i];
		i++;
	}
}

void	prefill_map(t_data *data)
{
	int i;
	int n;

	i = 0;

	data->map = (unsigned char *)malloc(sizeof(unsigned char) * MEM_SIZE);

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

//	ft_print_memory(data->map, MEM_SIZE);
	print_map(data);
}
