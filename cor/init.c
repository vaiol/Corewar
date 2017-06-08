//
// Created by Ivan Solomakhin on 5/18/17.
//

#include "corewar.h"

void	init_map(t_data *data)
{
	int n;

	prefill_map(data);

	n = -1;
	while (++n < data->count)
		fill_map(data, &data->champs[n]);

	data->print.time_to_die = CYCLE_TO_DIE;
	data->print.nbr_live = 0;
	data->speed = 100;
	data->max_checks = 0;
}

void	init_carriage(t_data *data)
{
	int r;
	int n;
	int pn;

	n = 0;
	while (n < data->count)
	{
		pn = n + 1;
		data->champs[n].last_live = 0;
		data->champs[n].carr_count = 1;
		data->champs[n].carriage = (t_carr *)malloc(sizeof(t_carr));

		data->champs[n].carriage->pn = n + 1;
		data->champs[n].carriage->valid = FALSE;
		data->champs[n].carriage->id = 1;
		data->champs[n].carriage->g_int = -1;
		data->champs[n].carriage->cycle = 0;
		data->champs[n].carriage->live = 0;
		data->champs[n].carriage->carry = FALSE;
		data->champs[n].carriage->index = data->champs[n].start_pos;
		data->champs[n].carriage->op.cycles = 1;
		data->champs[n].carriage->op.opcode = 0;
		data->champs[n].carriage->t_ind = 0;
		data->champs[n].carriage->reg[1] = -pn;
		r = 2;
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