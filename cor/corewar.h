
#ifndef COREWAR_H
# define COREWAR_H

# include "../op.h"
# include "../libft/libft.h"
# include <fcntl.h>



typedef struct	s_champ
{
	size_t			size;
	char			*code;

}				t_champ;


typedef struct	s_fl
{
	int			flags;
	int			n;

}				t_fl;

typedef struct	s_data
{
	int			index;
	int			count;
	t_fl		fl;
	t_champ		*champs;

}				t_data;

// error_handler

void			error_handler(char *str);

// get_flags

void			check_flags(int argc, char **argv, t_data *data);

// get_files

void			get_files(t_data *data, char **argv);

// utils

void			count_files(t_data *data, char **argv);

#endif
