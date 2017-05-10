
#ifndef COREWAR_H
# define COREWAR_H

#include "../libft/libft.h"
#include "../libft/get_next_line/get_next_line.h"
#include "../libft/ft_printf/ft_printf.h"


typedef struct	s_fl
{
	int			flags;
	int			n;

}				t_fl;

typedef struct	s_data
{

	t_fl		fl;

}				t_data;


void			error_handler(char *str);
void			check_flags(int argc, char **argv, t_data *data);

#endif
