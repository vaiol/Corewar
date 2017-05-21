
#ifndef COREWAR_H
# define COREWAR_H

//# include "../op.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <ncurses.h>
# include <stdio.h>


# define IND_SIZE 2
# define REG_SIZE 4
# define DIR_SIZE REG_SIZE

# define OP_COUNT 17


# define REG_CODE 1
# define DIR_CODE 2
# define IND_CODE 3


# define MAX_ARGS_NUMBER 4
# define MAX_PLAYERS 4
# define MEM_SIZE (4 * 1024)
# define IDX_MOD (MEM_SIZE / 8)
# define CHAMP_MAX_SIZE (MEM_SIZE / 6)

# define COMMENT_CHAR '#'
# define LABEL_CHAR ':'
# define DIRECT_CHAR '%'
# define SEPARATOR_CHAR ','

# define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING ".name"
# define COMMENT_CMD_STRING ".comment"

# define REG_NUMBER 16

# define CYCLE_TO_DIE 1536
# define CYCLE_DELTA 50
# define NBR_LIVE 21
# define MAX_CHECKS 10

typedef char	t_arg_type;

#define T_REG 1
#define T_DIR 2
#define T_IND 4
#define T_LAB 8

# define PROG_NAME_LENGTH (128)
# define COMMENT_LENGTH (2048)
# define COREWAR_EXEC_MAGIC 0xea83f3

# define GREEN "\x1B[32m\0"
# define BLUE "\x1B[34m\0"
# define RED "\x1B[31m\0"
# define CYAN "\x1B[36m\0"
# define BLACK "\x1B[30m\0"
# define EOC "\x1B[0m\0"

// game speed (visual update)
# define NC_SPEED 20


// corewar windows and stats for ncurses
typedef struct		s_print
{
	WINDOW 			*win_corwar;
	WINDOW			*win_map;
	WINDOW			*win_stat;
	int				cycle_to_die;
	size_t			cycle;
	int				status;
}					t_print;

// corewar rules and stats
typedef struct		s_rules
{
	int				cycle_to_die;
	size_t			cycle;
	int				status;
}					t_rules;

// map struct
typedef struct		s_map
{
//	player number flag
	int				pn;
//  carriage flag for visual effect
	int				carriage;
//	what inside this mem cell
	unsigned char   cell;
}					t_map;

//	carriage struct
typedef struct		s_carr
{
	int				index;
	int				reg[16 + 1];
	struct s_carr	*next;
}					t_carr;

//	champion struct
typedef struct		s_champ
{
	int				nb;
	int				start_pos;
	char			*file_name;
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	size_t			real_prog_size;
	char			comment[COMMENT_LENGTH + 1];
	char			*program;
//	carriage
	t_carr			*carriage;
}					t_champ;

//	flags struct
typedef struct		s_fl
{
	int				flags;
	int				n;
}					t_fl;

//	main struct
typedef struct		s_data
{
	int				index;
	int				count;
	t_fl			fl;
	t_champ			*champs;
	t_map			map[MEM_SIZE];
	t_print			print;
	t_rules			rules;
}					t_data;

// carriage.c

///////// empty for now

// corewar

void				corewar(t_data *data);
void				manage_corewar(t_data *data);

// error_handler.c

void				error_handler(char *str);
void				champ_error_handler(char *str, char *champion);

// get_flags.c

void				check_flags(int argc, char **argv, t_data *data);

// get_files.c

void				get_files(t_data *data, char **argv);

// init.c

void				init_corewar(t_data *data);

// map.c

void				prefill_map(t_data *data);
void				fill_map(t_data *data, t_champ *champ);
void				print_map(t_data *data);

// nc_print.c

void				nc_print_map(t_data *data, WINDOW *win);
void				nc_print_stat(t_data *data, WINDOW *win);

// nc_print_stat.c

void				print_stat_status(t_data *data, WINDOW *win);
void				print_stat_cycle(t_data *data, WINDOW *win);
void				print_num_processes(t_data *data, WINDOW *win);
void				print_champs(t_data *data, WINDOW *win);
void				print_rules(t_data *data, WINDOW *win);

// nc_utils.c

void				get_color(int pn, WINDOW *win);
void				get_carriage_color(int pn, WINDOW *win);
void				nc_refresh(t_data *data, t_print *print);
void				shut_down_nc(t_data *data);

// ncurses.c

void				init_ncurses(t_data *data, t_print *print);
void				nc_start(t_data *data);
void				nc_pause(t_data *data);

// utils.c

void				count_files(t_data *data, char **argv);
int					get_magic(unsigned char *str);

#endif
