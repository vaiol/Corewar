LIB     = ../libft/
NAME    = corewar
CFLAGS  = -Wall -Wextra -Werror
CC      = gcc

SRCS    =   champ_functions/add_sub.c \
            champ_functions/aff.c \
            champ_functions/and_or_xor.c \
            champ_functions/fork_lfork.c \
            champ_functions/ld_ldi_lldi.c \
            champ_functions/live.c \
            champ_functions/st_sti.c \
            champ_functions/zjmp.c \
            nc/nc_print.c \
            nc/nc_print_stat.c \
            nc/nc_print_winner.c \
            nc/nc_utils.c \
            nc/ncurses.c \
            carriage.c \
            carriage_func.c \
            champ_checks.c \
            corewar.c \
            count_champs.c \
            error_handler.c \
            get_flags.c \
            init.c \
            main.c \
            manage_files.c \
            manage_function.c \
            map.c \
            opcode.c \
            parse_function.c \
            print_logs.c \
            set_num_and_pos.c \
            time_to_die.c \
            utils.c \
            validate_function.c \
            winner.c

OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@printf "[CC] libft.a start:\n"
	@make -C $(LIB)
	@printf "[CC] libft.a finished successfull!\n"
	@$(CC) $(SRCS) -lncurses $(LIB)libft.a -o $(NAME)
	@printf "[CC] %s\n" $(NAME)

.c.o:
	@printf "[CC] %s                                                  \r" $<
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@printf "[RM] objects\n"
	@rm -rf $(OBJS)
	@make -C $(LIB) clean

fclean: clean
	@printf "[RM] %s libft/libft.a\n" $(NAME)
	@rm -rf $(NAME)
	@make -C $(LIB) fclean

re: fclean all
