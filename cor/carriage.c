//
// Created by Ivan Solomakhin on 5/18/17.
//

#include "corewar.h"

void	clear_op(t_carr *carr)
{
	carr->binary = NULL;
	carr->t_ind = 0;
	carr->arg_type[0] = 0;
	carr->arg_type[1] = 0;
	carr->arg_type[2] = 0;

	carr->op.name = NULL;
	carr->op.count_args = 0;
	carr->op.args[0] = 0;
	carr->op.args[1] = 0;
	carr->op.args[2] = 0;
	carr->op.opcode = 0;
	carr->op.cycles = 0;
	carr->op.octal_coding = 0;
	carr->op.label_size = 0;
}

void	fork_carriage(t_data *data, t_carr *carr, int index)
{
	int		r;
	t_carr	*new_carr;
	t_carr	*current;

	new_carr = (t_carr *)malloc(sizeof(t_carr));
	new_carr->pn = carr->pn;
	new_carr->index = index;
	new_carr->carry = carr->carry;
	new_carr->next = NULL;

	r = 0;
	while (++r < 17)
		new_carr->reg[r] = carr->reg[r];
	clear_op(new_carr);

	current = data->champs[carr->pn].carriage;
	while (current != NULL)
		current = current->next;
	current = new_carr;
}

void	kill_carriage(t_data *data, t_carr *carr)
{
	t_carr *head;
	t_carr *del;
	t_carr *prev;

	head = data->champs[carr->pn].carriage;
	if (head->cycle > data->print.cycle_to_die)
	{
		if (head->next == NULL)
			return ;
		del = head;
		head = head->next;
		free (del);
		return;
	}
	prev = head;
	while (prev->next != NULL && prev->next->cycle <= data->print.cycle_to_die)
		prev = prev->next;

	if(prev->next == NULL)
		return;
	del = prev->next;
	prev->next = prev->next->next;
	free(del);
}

//void	init_carriage(t_data *data)
//{
//	int r;
//	int n;
//
//	n = 0;
//	while (n < data->count)
//	{
//		data->champs[n].carriage = (t_carr *)malloc(sizeof(t_carr));
//		data->champs[n].carriage->index = 0;
//		r = 0;
//		while (r < 17)
//		{
//			data->champs[n].carriage->reg[r] = 0;
//			r++;
//		}
//		data->champs[n].carriage->next = NULL;
//		n++;
//	}
//}
