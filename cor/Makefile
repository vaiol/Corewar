LIB     = ../libft/
NAME    = corewar
CFLAGS  = -Wall -Wextra -Werror
CC      = gcc

SRCS    =   map.c \
            error_handler.c \
            get_files.c \
            get_flags.c \
            main.c \
            utils.c



OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@printf "[CC] libft.a start:\n"
	@make -C $(LIB)
	@printf "[CC] libft.a finished successfull!\n"
	@$(CC) $(SRCS) $(LIB)libft.a -o $(NAME)
	@printf "[CC] %s\n" $(NAME)

.c.o:
	@printf "[CC] %s\n" $<
	@$(CC) $(CFLAGS) -c $<  -o $@

clean:
	@printf "[RM] objects\n"
	@rm -rf $(OBJS)
	@make -C $(LIB) clean

fclean: clean
	@printf "[RM] %s libft/libft.a\n" $(NAME)
	@rm -rf $(NAME)
	@make -C $(LIB) fclean

re: fclean all
