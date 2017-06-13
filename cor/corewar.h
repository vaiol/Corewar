/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 17:39:36 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:54:58 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <ncurses.h>
# include <stdio.h>

# define OP_COUNT 17
# define MEM_SIZE (4 * 1024)
# define IDX_MOD (MEM_SIZE / 8)
# define CHAMP_MAX_SIZE (MEM_SIZE / 6)
# define CYCLE_TO_DIE 1536
# define CYCLE_DELTA 50
# define NBR_LIVE 21
# define MAX_CHECKS 10
# define T_REG 1
# define T_DIR 2
# define T_IND 4
# define PROG_NAME_LENGTH (128)
# define COMMENT_LENGTH (2048)
# define COREWAR_EXEC_MAGIC 0xea83f3
# define GREEN "\x1B[32m\0"
# define BLUE "\x1B[34m\0"
# define RED "\x1B[31m\0"
# define CYAN "\x1B[36m\0"
# define WHITE "\x1B[37m\0"
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

typedef struct		s_print
{
	WINDOW			*win_corwar;
	WINDOW			*win_map;
	WINDOW			*win_stat;
	WINDOW			*win;
	WINDOW			*border;
	int				nbr_live;
	int				time_to_die;
	int				cycle_to_die;
	int				cycle;
	int				status;
}					t_print;

typedef struct		s_map
{
	int				pn;
	int				carriage;
	unsigned char	cell;
}					t_map;

typedef struct		s_carr
{
	int				pn;
	int				index;
	int				g_int;
	int				valid;
	int				carry;
	int				live;
	int				id;
	char			*binary;
	int				t_ind;
	int				arg_type[3];
	int				reg[1 + 16];
	t_op			op;
	struct s_carr	*next;
}					t_carr;

typedef struct		s_champ
{
	int				nb;

	int				nb_set;
	int				start_pos;
	char			*file_name;
	int				last_live;
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	size_t			real_prog_size;
	char			comment[COMMENT_LENGTH + 1];
	char			*program;
	int				carr_count;
}					t_champ;

typedef struct		s_fl
{
	int				flags;
	int				l;
	int				v;
	int				a;
	int				n;
}					t_fl;

typedef struct		s_data
{
	int				index;
	int				count;
	int				dump;
	int				speed;
	int				max_checks;
	int				nb;
	int				car_count;
	int				winner;
	t_fl			fl;
	t_champ			*champs;
	t_carr			*carr;
//	t_map			map[MEM_SIZE];
	t_map			*map;
	t_print			print;
}					t_data;

/*
 ** carriage.c
*/
void				clear_op(t_carr *carr);
void				fork_carriage(t_data *data, t_carr *carr, int index);
void				kill_carriage(t_data *data, t_carr *carr);

/*
 ** carriage_func.c
*/
void				wait_carriage(t_data *data, t_carr *current);
void				move_carriage(t_data *data, t_carr *current);
void				move_to_temp(t_data *data, t_carr *current);
void				carriage_cycle(t_data *data, t_carr *carr);

/*
 ** corewar.c
*/
void				corewar(t_data *data);
void				manage_corewar(t_data *data);

/*
 ** error_handler.c
*/
void				error_handler(char *str);
void				champ_error_handler(char *str, char *champion);
void				error_handler_usage(void);

/*
 ** get_flags.c
*/
void				check_flags(t_data *data, int argc, char **argv);

/*
 ** get_files.c
*/
void				get_files(t_data *data, char **argv);
void				manage_file(t_data *data, char *argv, int nb);

/*
 ** init.c
*/
void				init_corewar(t_data *data);

/*
 ** manage_function.c
*/
void				manage_function(t_data *data, t_carr *carr);
void				get_wait_cycle(t_carr *carr);
void				place_on_map(t_carr *carr, t_map *map, int nbr, int index);
int					get_indirect_from_map(t_map *map, int index);
void				manage_carry(t_carr *carr, int res);

/*
 ** map.c
*/
void				prefill_map(t_data *data);
void				fill_map(t_data *data, t_champ *champ);
void				print_map(t_data *data);

/*
 ** nc_print.c
*/
void				nc_print_map(t_data *data, WINDOW *win);
void				nc_print_stat(t_data *data, WINDOW *win);

/*
 ** nc_print_stat.c
*/
void				print_stat_status(t_data *data, WINDOW *win);
void				print_stat_cycle(t_data *data, WINDOW *win);
void				print_num_processes(t_data *data, WINDOW *win);
void				print_champs(t_data *data, WINDOW *win);
void				print_rules(t_data *data, WINDOW *win);

/*
 ** nc_print_winner
*/
void				nc_print_winner(t_data *data, t_print *p, int winner);

/*
 ** nc_utils.c
*/
void				change_speed(t_data *data, int key);
void				get_color(int pn, WINDOW *win);
void				get_carriage_color(int pn, WINDOW *win);
void				nc_refresh(t_data *data, t_print *print);
void				shut_down_nc(t_data *data);

/*
 ** ncurses.c
*/
void				init_ncurses(t_data *data, t_print *print);
void				nc_start(t_data *data);
void				nc_pause(t_data *data);

/*
 ** opcode.c
*/
void				read_cell(t_data *data, t_carr *carr);
int					get_opcode(t_data *data, t_carr *carr, int i);
void				get_octal_coding(t_data *data, t_carr *carr, int i);

/*
 ** parse_function.c
*/
void				parse_octal(t_data *data, t_carr *carr, unsigned label);
void				parse_non_octal(t_data *data, t_carr *carr, unsigned label);

/*
 ** print_logs.c
*/
void				print_function(t_data *data, t_carr *carr);
void				print_cycle(t_data *data);
void				print_movements(t_data *data, t_carr *carr);
void				print_cycle_to_die(t_data *data);

/*
 ** utils.c
*/
int					unsigned_to_int(unsigned nbr);
int					char_to_int(unsigned char *str);
char				*to_two_base(unsigned char c);
unsigned char		*int_to_str(int n);
int					count_processes(t_data *data);

/*
 ** validate_function.c
*/
int					validate_function(t_carr *carr, unsigned opcode);

/*
 ** winner.c
*/
void				print_winner(t_data *data);

/*
 ** functions
*/
void				function_live(t_data *data, t_carr *carr);
void				function_ld(t_data *data, t_carr *carr, int *args);
void				function_ldi(t_data *data, t_carr *carr, int *args);
void				function_lld(t_data *data, t_carr *carr, int *args);
void				function_lldi(t_data *data, t_carr *carr, int *args);
void				function_st(t_data *data, t_carr *carr);
void				function_sti(t_data *data, t_carr *carr, int *args);
void				func_add_sub(t_data *data, t_carr *carr, int *args, int nb);
void				func_and_or(t_data *data, t_carr *carr, int *args, int nb);
void				function_zjmp(t_data *data, t_carr *carr);
void				function_aff(t_data *data, t_carr *carr);
void				function_fork(t_data *data, t_carr *carr, unsigned opcode);

/*
** time_to_die
*/
void				time_to_die(t_data *data);

/*
 ** set_num_and_pos
*/
void				set_default_num(t_data *data, int nb, int number);
void				set_start_pos(t_data *data, t_champ *champ, int nb);

/*
 ** champ_checks
*/
void				check_magic(t_champ *champ, char *content);
int					check_prog_name(t_champ *champ, char *content, size_t sh);
void				check_prog_size(t_champ *champ, size_t shift);
int					check_comment(t_champ *champ, char *content, size_t shift);
void				check_program(t_champ *champ, char *content, size_t shift);

#endif
