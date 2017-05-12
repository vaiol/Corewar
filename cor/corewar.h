
#ifndef COREWAR_H
# define COREWAR_H

//# include "../op.h"
# include "../libft/libft.h"
# include <fcntl.h>

# define MAX_ARGS_NUMBER 4
# define MAX_PLAYERS 4
# define MEM_SIZE (4 * 1024)
# define IDX_MOD (MEM_SIZE / 8)
# define CHAMP_MAX_SIZE (MEM_SIZE / 6)

# define PROG_NAME_LENGTH (128)
# define COMMENT_LENGTH (2048)
# define COREWAR_EXEC_MAGIC 0xea83f3

typedef struct	s_champ
{
	int				nb;
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
	char			*program;
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
