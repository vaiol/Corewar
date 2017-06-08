//
// Created by Ivan Solomakhin on 6/7/17.
//

#include "corewar.h"

int		get_winner(t_data *data)
{
	int n;
	int winner;
	int last_live;

	n = -1;
	winner = 0;
	last_live = 0;
	while (++n < data->count)
	{
		if (data->champs[n].last_live > last_live)
			winner = n;
	}
	return (n);
}

void	print_winner(t_data *data)
{
	char *name;

	int winner = get_winner(data);
	if (data->fl.v > 0)
		nc_print_winner(data, winner - 1);
	else
	{
		name = data->champs[winner - 1].prog_name;
		ft_printf("Contestant %i, \"%s\", has won !\n", winner, name);
		shut_down_nc(data);
	}
}
