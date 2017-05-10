
#ifndef COREWAR_H
# define COREWAR_H

# include "../libft/libft.h"
# include "../libft/get_next_line/get_next_line.h"
# include "../libft/ft_printf/ft_printf.h"

# include <fcntl.h>

# define MAX_ARGS_NUMBER			4
# define MAX_PLAYERS				4
# define MEM_SIZE				(4*1024)
# define IDX_MOD					(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)

typedef struct	s_champ
{
	size_t		size;
	char		*code;

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
