
#include "corewar.h"

//void	manage_ld(t_data *data, t_carr *carr)
//{
//	int coding = g_op_tab[0].octal_coding;
//
//}

/* Create a string of binary digits based on the input value.
   Input:
       val:  value to convert.
       buff: buffer to write to must be >= sz+1 chars.
       sz:   size of buffer.
   Returns address of string or NULL if not enough space provided.
*/
//static char *binrep (unsigned int val, char *buff, int sz) {
//	char *pbuff = buff;
//
//	/* Must be able to store one character at least. */
//	if (sz < 1) return NULL;
//
//	/* Special case for zero to ensure some output. */
//	if (val == 0) {
//		*pbuff++ = '0';
//		*pbuff = '\0';
//		return buff;
//	}
//
//	/* Work from the end of the buffer back. */
//	pbuff += sz;
//	*pbuff-- = '\0';
//
//	/* For each bit (going backwards) store character. */
//	while (val != 0) {
//		if (sz-- == 0) return NULL;
//		*pbuff-- = ((val & 1) == 1) ? '1' : '0';
//
//		/* Get next bit. */
//		val >>= 1;
//	}
//	return pbuff+1;
//}

char	*to_two_base(unsigned char nbr)
{
	int		i;
//	char	octal[8];
	char	*octal = ft_strnew(7);

//	if nbr == zero ??????

	i = 7;
	while (nbr != 0 && i >= 0)
	{
		if ((nbr & 1) == 1)
			octal[i] = '1';
		else
			octal[i] = '0';
		nbr >>= 1;
		i++;
	}
	return octal;
}

void	parse_octal(t_data *data, t_carr *carr)
{
	char *octal;

	octal = to_two_base(data->map[carr->index + 1].cell);
	ft_printf("OCTAL = %s\n", octal);
}

void	get_octal_coding(t_data *data, t_carr *carr, int i)
{
	if (g_op_tab[i].octal_coding)
	{
		parse_octal(data, carr);
	}
	else
	{
		;
	}
}

int		get_opcode(t_data *data, t_carr *carr, int i)
{
	if (data->map[carr->index].cell == g_op_tab[i].opcode)
	{
		carr->op.opcode = g_op_tab[i].opcode;
		get_octal_coding(data, carr, i);
		return (TRUE);
	}
	return (FALSE);
}

void	read_cell(t_data *data, t_carr *carr)
{
	int			i;

	i = 0;
	while (get_opcode(data, carr, i) != TRUE && i < OP_COUNT)
	{
		i++;
	}
}

void	manage_corewar(t_data *data)
{
	int		n;
	t_carr *current;

	n = -1;
	while (++n < data->count)
	{
		current = data->champs[n].carriage;
		while (current != NULL)
		{
//
			read_cell(data, current);
//
			data->map[current->index].carriage = 0;
			if (current->index >= MEM_SIZE)
				current->index = -1;
			current->index++;

			data->map[current->index].carriage = 1;
			current = current->next;
		}
	}
}

void	corewar(t_data *data)
{
	if (data->fl.flags > 0)
	{
		if (data->fl.n == 1)
		{
			init_ncurses(data, &data->print);
			nc_pause(data);
		}
	}
	else
	{
		//	for testing
//		print_map(data);
		ft_printf("Use -n flag\n");

		int i = 0;
		while (i < 1)
		{
			manage_corewar(data);
			ft_printf("\n");
			i++;
		}
	}
}

//01110000