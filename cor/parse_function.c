//
// Created by Ivan Solomakhin on 5/24/17.
//

#include "corewar.h"

int		get_register(t_data *data, t_carr *carr, int i)
{
	int	nb_reg;
	carr->op.count_args++;
	carr->arg_type[i] = T_REG;
//	if ((int)c >= 0 && (int)c <= 16)
// 	bigger than 16 ???????
	nb_reg = (int)data->map[carr->index + carr->t_ind].cell;
	ft_printf("register = %i\n", (int)data->map[carr->index + carr->t_ind].cell);
	carr->t_ind++;
	return (nb_reg);
}

int		get_direct(t_data *data, t_carr *carr, unsigned label, int i)
{
	int		nbr;
	unsigned char	str[4];

	str[0] = data->map[carr->index + carr->t_ind].cell;
	carr->t_ind++;
	str[1] = data->map[carr->index + carr->t_ind].cell;
	carr->t_ind++;
	str[2] = data->map[carr->index + carr->t_ind].cell;
	carr->t_ind++;
	str[3] = data->map[carr->index + carr->t_ind].cell;
	carr->t_ind++;
	if (label)
	{
		nbr = (str[0] << 8) + str[1];
		carr->t_ind -= 2;
	}
	else
		nbr = char_to_int(str);

	ft_printf("direct = %i\n", nbr);

	carr->arg_type[i] = T_DIR;
	carr->op.count_args++;
	return (nbr);
}

int		get_indirect(t_data *data, t_carr *carr, int i)
{
	int		nbr;
	char	one;
	char	two;

	one = data->map[carr->index + carr->t_ind].cell;
	carr->t_ind++;
	two = data->map[carr->index + carr->t_ind].cell;
	carr->t_ind++;

	nbr = (one << 8) + two;

	ft_printf("indirect = %i\n", nbr);

	carr->arg_type[i] = T_IND;
	carr->op.count_args++;
	return (nbr);

}

void	parse_octal(t_data *data, t_carr *carr, unsigned label)
{
	int		i;
	int		one;
	int		two;

	carr->binary = to_two_base(data->map[carr->index + carr->t_ind].cell);
	ft_printf("function : %s\nbinary = %s\n", carr->op.name, carr->binary);
	carr->t_ind++;
	i = 0;
	one = 0;
	two = 1;
	while (two <= 7)
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