//
// Created by Ivan Solomakhin on 5/18/17.
//

#include "corewar.h"

void	clear_op(t_carr *carr)
{
	carr->binary = NULL;
	carr->t_ind = 0;
	carr->valid = FALSE;
	carr->g_int = -1;

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

//t_carr	*kill_carriage(t_data *data, t_carr *carr)
//{
//	t_carr *head;
//	t_carr *del;
//	t_carr *prev;
//
//	data->map[carr->index].carriage = 0;
//
////	ft_printf("carriage %i die\n", carr->id);
//
//	head = data->champs[carr->pn - 1].carriage;
//	if (head == carr)
//	{
////		ft_printf("this need to die\n");
//		if (head->next == NULL)
//		{
////			ft_printf("this need to die\n");
//			data->champs[carr->pn - 1].carriage = NULL;
////			exit(1);
////			shut_down_nc(data);
//			return (NULL);
//		}
////		del = head;
//		data->champs[carr->pn - 1].carriage = head->next;
////		head = head->next;
////		free (del);
//		return (data->champs[carr->pn - 1].carriage);
//	}
//	prev = head;
//	while (prev->next != NULL && prev->next != carr)
//		prev = prev->next;
//
////	ft_printf("kill index = %i\n", prev->next->index);
//	del = prev->next;
//	prev->next = prev->next->next;
//	free(del);
//	return (prev->next);
//}

t_carr	*kill_carriage(t_data *data, t_carr *carr)
{
	t_carr *head;
	t_carr *del;
	t_carr *prev;

	data->map[carr->index].carriage = 0;

//	ft_printf("carriage %i die\n", carr->id);

	head = data->carr;
	if (head == carr)
	{
//		ft_printf("this need to die\n");
		if (head->next == NULL)
		{
//			ft_printf("this need to die\n");
			data->carr = NULL;
//			exit(1);
//			shut_down_nc(data);
			return (NULL);
		}
//		del = head;
		data->carr = head->next;
//		head = head->next;
//		free (del);
		return (data->carr);
	}
	prev = head;
	while (prev->next != NULL && prev->next != carr)
		prev = prev->next;

//	ft_printf("kill index = %i\n", prev->next->index);
	del = prev->next;
	prev->next = prev->next->next;
	free(del);
	return (prev->next);
}

void	fork_carriage(t_data *data, t_carr *carr, int index)
{
	int r;
	t_carr *new_carr;
	t_carr *old_head;

	data->champs[carr->pn - 1].carr_count++;

	new_carr = (t_carr *)malloc(sizeof(t_carr));

//	new_carr->id = data->champs[carr->pn - 1].carr_count;
	new_carr->id = data->car_count;
	data->car_count++;
	new_carr->pn = carr->pn;

	new_carr->index = index;
//	new_carr->live = 0;
	new_carr->live = carr->live;
	new_carr->carry = carr->carry;

	r = 0;
	while (++r < 17)
		new_carr->reg[r] = carr->reg[r];
	clear_op(new_carr);

	old_head = data->carr;
	new_carr->next = old_head;
	data->carr = new_carr;
}

//void	fork_carriage(t_data *data, t_carr *carr, int index)
//{
//	int r;
//	t_carr *new_carr;
//	t_carr *old_head;
//
//	data->champs[carr->pn - 1].carr_count++;
//
//	new_carr = (t_carr *) malloc(sizeof(t_carr));
//
//	new_carr->id = data->champs[carr->pn - 1].carr_count;
//	new_carr->pn = carr->pn;
//
//	new_carr->index = index;
//	new_carr->live = 0;
//	new_carr->carry = carr->carry;
//
//	r = 0;
//	while (++r < 17)
//		new_carr->reg[r] = carr->reg[r];
//	clear_op(new_carr);
//
//	old_head = data->champs[carr->pn - 1].carriage;
//	new_carr->next = old_head;
//	data->champs[carr->pn - 1].carriage = new_carr;
//}
