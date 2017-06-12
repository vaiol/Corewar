//
// Created by Ivan Solomakhin on 6/7/17.
//

#include "corewar.h"

int		get_winner(t_data *data)
{
	int n;
	int winner;
	int last_live;

	winner = 0;
	last_live = 0;
	n = -1;
	while (++n < data->count)
//	n = data->count;
//	while (--n >= 0)
	{
		ft_printf("n = %i\n", n);
		if (data->champs[n].last_live >= last_live)
		{
			last_live = data->champs[n].last_live;
			winner = n;
		}
	}
	return (winner);
}

void	print_winner(t_data *data)
{
	char	*name;
	int		winner;

//	winner = get_winner(data);
	winner = data->winner;
	if (data->fl.v > 0)
		nc_print_winner(data, winner);
	else
	{
		name = data->champs[winner].prog_name;
		ft_printf("Contestant %i, \"%s\", has won !\n", winner + 1, name);
		shut_down_nc(data);
	}
}
