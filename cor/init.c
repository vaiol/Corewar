//
// Created by Ivan Solomakhin on 5/18/17.
//

#include "corewar.h"

void	init_map(t_data *data)
{
	int n;

	prefill_map(data);

//	while (1);

	n = -1;
	while (++n < data->count)
		fill_map(data, &data->champs[n]);
	data->print.time_to_die = CYCLE_TO_DIE;
	data->print.nbr_live = 0;
	data->speed = 100;
	data->max_checks = 0;
	data->car_count = 1;
	data->winner = 0;
}


t_carr	*create_carriage(t_data *data, int n)
{
	int pn;
	int		r;
	t_carr	*carr;

	pn = n + 1;
	data->champs[n].last_live = 0;
	data->champs[n].carr_count = 1;
	carr = (t_carr *)malloc(sizeof(t_carr));
	carr->pn = n + 1;
	carr->valid = FALSE;
//
	carr->id = data->car_count;
	data->car_count++;
//
	carr->g_int = -1;
	carr->cycle = 0;
	carr->live = 0;
	carr->carry = FALSE;
	carr->index = data->champs[n].start_pos;
	carr->op.cycles = 1;
	carr->op.opcode = 0;
	carr->t_ind = 0;
//	carr->reg[1] = -pn;
	carr->reg[1] = data->champs[n].nb_set;
	ft_printf("nb set = %i\n", carr->reg[1]);
	r = 1;
	while (++r < 17)
		carr->reg[r] = 0;
	carr->next = NULL;
	return (carr);
}

void	init_carriage(t_data *data)
{
	int		n;
	t_carr *new_carr;

	data->carr = NULL;
	n = -1;
	while (++n < data->count)
	{
		if (data->carr == NULL)
			data->carr = create_carriage(data, n);
		else
		{
			new_carr = create_carriage(data, n);
			new_carr->next = data->carr;
			data->carr = new_carr;
		}
	}
}

void	init_corewar(t_data *data)
{
	init_map(data);
	init_carriage(data);

}