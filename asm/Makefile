# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astepano <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/03 15:03:21 by astepano          #+#    #+#              #
#    Updated: 2017/05/01 18:46:46 by astepano         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB     = ../libft/
NAME    = asm
CFLAGS  = -Wall -Wextra -Werror
CC      = gcc
PREF     = asm_
ADD      = additionals
SRCS    =   main.c \
            $(PREF)validate_content.c \
            $(PREF)validate_operations.c \
            $(PREF)read_file.c \
            $(PREF)parse_file.c \
            $(PREF)parse_operations.c \
            $(PREF)generate_byte_operations.c \
            $(PREF)generate_byte_code.c \
            $(ADD)/$(PREF)compare_str.c \
            $(ADD)/$(PREF)create_content.c \
            $(ADD)/$(PREF)create_operation.c \
            $(ADD)/$(PREF)file_name.c \
            $(ADD)/$(PREF)get_prog_len.c \
            $(ADD)/$(PREF)get_magic.c \
            $(ADD)/$(PREF)get_label.c \
            $(ADD)/$(PREF)generate_string.c \
            $(ADD)/$(PREF)invalid_type_message.c \
            $(ADD)/$(PREF)is_arg.c \
            $(ADD)/$(PREF)label_exist.c \
            $(ADD)/$(PREF)skip_spaces.c \
            $(ADD)/$(PREF)arrjoin.c \
            $(ADD)/$(PREF)get_position.c
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
