//
// Created by Ivan Solomakhin on 5/24/17.
//

#include "corewar.h"

//void	check_end_of_map(t_carr *carr)
//{
//	if (carr->t_ind > MEM_SIZE)
//		carr->t_ind = 0;
//}

int		get_register(t_data *data, t_carr *carr, int i)
{
	int index;
	int	nb_reg;

	index = carr->index + carr->t_ind;

	if (index >= MEM_SIZE)
		index = (carr->index + carr->t_ind) - MEM_SIZE;

	nb_reg = (int)data->map[index].cell;

	carr->arg_type[i] = T_REG;
	carr->t_ind++;
//	ft_printf("register = %i from cell nb = %i with %x \n", nb_reg, index, data->map[index].cell);

	return (nb_reg);
}

int		get_direct(t_data *data, t_carr *carr, unsigned label, int i)
{
	unsigned int	nbr;
	unsigned char	str[4];
	int j;
	int index;

	index = carr->index + carr->t_ind;

	j = -1;
	while (++j < 4)
	{
		if (index >= MEM_SIZE)
			index = (carr->index + carr->t_ind) - MEM_SIZE;
		str[j] = data->map[index].cell;
		index++;
		carr->t_ind++;
	}

	if (label)
	{
		nbr = (short)(str[0] << 8) + str[1];
//		ft_printf("direct = %i %i, str[0] = %x & str[1] = %x\n", nbr, label, str[0], str[1]);
		carr->t_ind -= 2;
	}
	else
		nbr = (str[0] << 24) + (str[1] << 16) + (str[2] << 8) + str[3];

	carr->arg_type[i] = T_DIR;

	return (nbr);
}

//int		get_direct(t_data *data, t_carr *carr, unsigned label, int i)
//{
//	unsigned int	nbr;
//	unsigned char	str[4];
//
//	str[0] = data->map[carr->index + carr->t_ind].cell;
//	carr->t_ind++;
//	str[1] = data->map[carr->index + carr->t_ind].cell;
//	carr->t_ind++;
//	str[2] = data->map[carr->index + carr->t_ind].cell;
//	carr->t_ind++;
//	str[3] = data->map[carr->index + carr->t_ind].cell;
//	carr->t_ind++;
//	if (label)
//	{
//		nbr = (short)(str[0] << 8) + str[1];
//		carr->t_ind -= 2;
//	}
//	else
//		nbr = (str[0] << 24) + (str[1] << 16) + (str[2] << 8) + str[3];
//
//	carr->arg_type[i] = T_DIR;
////	carr->op.count_args++;
//	return (nbr);
//}

int		get_indirect(t_data *data, t_carr *carr, int i)
{
	unsigned int		nbr;
	unsigned char	one;
	unsigned char	two;

	int 			index;

	index = carr->index + carr->t_ind;

	if (index >= MEM_SIZE)
		index = (carr->index + carr->t_ind) - MEM_SIZE;

	one = data->map[index].cell;
	index++;
	carr->t_ind++;
	two = data->map[index].cell;
	carr->t_ind++;

	nbr = (short)((one << 8) + two);

//	ft_printf("indirect = %i\n", nbr);

	carr->arg_type[i] = T_IND;
//	carr->op.count_args++;



	return (nbr);

}

void	parse_octal(t_data *data, t_carr *carr, unsigned label)
{
	int		i;
	int		one;
	int		two;

	carr->binary = to_two_base(data->map[carr->index + carr->t_ind].cell);
	carr->t_ind++;
	i = 0;
	one = 0;
	two = 1;

//	ft_printf("Binary = %s t_id = %i n args %i\n", carr->binary, carr->id, carr->op.count_args);

//	ft_printf("was here\n");

	while (two <= ((int)carr->op.count_args * 2) - 1)
	{
		if (carr->binary[one] == '0' && carr->binary[two] == '1')
			carr->op.args[i] = get_register(data, carr, i);
		else if (carr->binary[one] == '1' && carr->binary[two] == '0')
			carr->op.args[i] = get_direct(data, carr, label, i);
		else if (carr->binary[one] == '1' && carr->binary[two] == '1')
			carr->op.args[i] = get_indirect(data, carr, i);
		i++;
		one += 2;
		two += 2;
	}

}

void	parse_non_octal(t_data *data, t_carr *carr, unsigned label)
{
	carr->op.args[0] = get_direct(data, carr, label, 0);
}