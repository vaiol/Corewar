//
// Created by Ivan Solomakhin on 5/18/17.
//

#include "corewar.h"

void	init_map(t_data *data)
{
	int n;

	prefill_map(data);

	n = 0;
	while (n < data->count)
	{
		fill_map(data, &data->champs[n]);
		n++;
	}
}

void	init_carriage(t_data *data)
{
	int r;
	int n;

	n = 0;
	while (n < data->count)
	{
		data->champs[n].carriage = (t_carr *)malloc(sizeof(t_carr));
		data->champs[n].carriage->pn = n;
		data->champs[n].carriage->index = data->champs[n].start_pos;
		data->champs[n].carriage->op.cycles = 0;
		data->champs[n].carriage->reg[0] = n;
		r = 1;
		while (r < 17)
		{
			data->champs[n].carriage->reg[r] = 0;
			r++;
		}
		data->champs[n].carriage->next = NULL;
		n++;
	}
}

void	init_corewar(t_data *data)
{
	init_map(data);
	init_carriage(data);
}