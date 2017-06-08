
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

# define TRUE 1
# define FALSE 0


typedef struct		s_op
{
	char			*name;
	unsigned		count_args;
	int				args[3];
	unsigned		opcode;
	unsigned		cycles;
	char			*comment;
	unsigned		octal_coding;
	unsigned		label_size;
}					t_op;

static const		t_op g_op_tab[17] =
		{
				{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
				{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
				{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
				{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
				{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
				{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
						"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
				{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
						"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
				{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
						"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
				{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
				{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
						"load index", 1, 1},
				{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
						"store index", 1, 1},
				{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
				{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
				{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
						"long load index", 1, 1},
				{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
				{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
				{0, 0, {0}, 0, 0, 0, 0, 0}
		};

// corewar windows and stats for ncurses
typedef struct		s_print
{
	WINDOW 			*win_corwar;
	WINDOW			*win_map;
	WINDOW			*win_stat;
	int				nbr_live;
	int				time_to_die;
	int				cycle_to_die;
	int				cycle;
	int				status;
}					t_print;

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
	int				pn; // always add + 1 to compare with r1;
	int				index;
	int				cycle;

	int				valid;
	int				g_int;

	int				carry;
	int				live;

	int				id;
//
	char			*binary;
	int				t_ind;
	int 			arg_type[3];
//
	int				reg[1 + 16];

	t_op			op;

	struct s_carr	*next;
}					t_carr;

//	champion struct
typedef struct		s_champ
{
	int				nb;

	int 			nb_set;
	int				start_pos;
	char			*file_name;
	int				last_live;
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	size_t			real_prog_size;
	char			comment[COMMENT_LENGTH + 1];
	char			*program;

	int 			carr_count;
//	carriage
	t_carr			*carriage;
}					t_champ;

//	flags struct
typedef struct		s_fl
{
	int				flags;
	int				l;
	int				v;
	int				a;
	int				n;
}					t_fl;

//	main struct
typedef struct		s_data
{
	int				index;
	int				count;
	int 			dump;
	int				speed;
	int 			max_checks;
	int				nb;
	t_fl			fl;
	t_champ			*champs;
	t_map			map[MEM_SIZE];
	t_print			print;
}					t_data;

// carriage.c

void				clear_op(t_carr *carr);
void				fork_carriage(t_data *data, t_carr *carr, int index);
t_carr				*kill_carriage(t_data *data, t_carr *carr);

// corewar

void				corewar(t_data *data);
void				manage_corewar(t_data *data);
void				move_to_temp(t_data *data, t_carr *current);

// error_handler.c

void				error_handler(char *str);
void				champ_error_handler(char *str, char *champion);
void 				error_handler_usage(void);

// get_flags.c

void				check_flags(t_data *data, int argc, char **argv);

// get_files.c

void				get_files(t_data *data, char **argv);
void				manage_file(t_data *data, char *argv, int nb);

// init.c

void				init_corewar(t_data *data);

// manage_function.c

void				manage_function(t_data *data, t_carr *carr);
void				get_wait_cycle(t_carr *carr);
int 				unsigned_to_int(unsigned nbr);
t_carr				*function_fork_lfork(t_data *data, t_carr *carr, unsigned opcode);

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

// nc_print_winner

void				nc_print_winner(t_data *data, int winner);

// nc_utils.c

void				get_color(int pn, WINDOW *win);
void				get_carriage_color(int pn, WINDOW *win);
void				nc_refresh(t_data *data, t_print *print);
void				shut_down_nc(t_data *data);

// ncurses.c

void				init_ncurses(t_data *data, t_print *print);
void				nc_start(t_data *data);
void				nc_pause(t_data *data);

// parse_function.c

void				parse_octal(t_data *data, t_carr *carr, unsigned label);
void				parse_non_octal(t_data *data, t_carr *carr, unsigned label);

// print_logs.c

void				print_function(t_data *data, t_carr *carr);
void 				print_cycle(t_data *data);
void				print_movements(t_data *data, t_carr *carr);
void				print_cycle_to_die(t_data *data);

// utils.c

void				count_files(t_data *data, char **argv);
int					char_to_int(unsigned char *str);
char				*to_two_base(unsigned char c);
unsigned char		*int_to_str(int n);
int					count_processes(t_data *data);

// validate_function.c

int					validate_function(t_carr *carr, unsigned opcode);

// winner.c

void				print_winner(t_data *data);

#endif
