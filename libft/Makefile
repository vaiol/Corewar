# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astepano <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/03 15:03:21 by astepano          #+#    #+#              #
#    Updated: 2017/03/22 13:14:54 by astepano         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PRINTF	= ft_printf/
PUTCONV	= put_conversion/
FLOAT	= $(PRINTF)$(PUTCONV)handle/float/pf_
UTIL	= $(PRINTF)$(PUTCONV)util/pf_
CONV	= $(PRINTF)$(PUTCONV)pf_put_
HANDLE	= $(PRINTF)$(PUTCONV)handle/pf_handle_
PUT	    = $(PRINTF)$(PUTCONV)put/pf_
PARSE	= $(PRINTF)parse_format/pf_parse_
GNL	    = get_next_line

LIB_SRCS	= ft_memset.c ft_strlen.c ft_strdup.c ft_strchr.c ft_strrchr.c	\
		  ft_strstr.c  ft_strcmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c	\
		  ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c		\
		  ft_tolower.c ft_strnew.c ft_strdel.c ft_strequ.c ft_strsub.c	\
		  ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_print_memory.c	\
		  ft_itoa_base.c ft_strcchr.c ft_strcut.c ft_pow.c		\
		  ft_strfjoin.c ft_strichr.c ft_arrdel.c ft_readfd.c ft_memcmp.c \
		  ft_atoi_base.c ft_itoa.c
GNL_SRCS	= $(GNL)/$(GNL).c $(GNL)/gnl_additionals.c
PRINTF_SRCS	= $(PRINTF)ft_printf.c						\
		  $(PUT)putstr.c $(PUT)write.c $(PUT)printed_count.c		\
		  $(UTIL)strjoinchr_begin.c $(UTIL)strjoinchr.c			\
		  $(UTIL)winttostr.c $(UTIL)wstrtostr.c $(UTIL)utoa_base.c	\
		  $(UTIL)strclear.c $(UTIL)zerocut.c				\
		  $(CONV)unsigned.c $(CONV)signed.c $(CONV)conversion.c		\
		  $(CONV)float.c $(CONV)unprintable.c $(CONV)string.c		\
		  $(CONV)char.c $(CONV)memory.c $(CONV)printed.c		\
		  $(PARSE)all.c  $(PARSE)flags.c $(PARSE)type.c			\
		  $(PARSE)minwidth.c $(PARSE)precision.c $(PARSE)size.c		\
		  $(PARSE)brace.c $(HANDLE)minwidth.c $(HANDLE)precision.c	\
		  $(HANDLE)apostrophe.c $(HANDLE)time.c	$(PARSE)additional.c \
		  $(FLOAT)additionals.c $(FLOAT)float.c $(FLOAT)frexpl.c	\
		  $(FLOAT)parsers.c $(FLOAT)rounder.c $(FLOAT)handle_e.c	\
		  $(FLOAT)handle_f.c $(FLOAT)handle_g.c $(FLOAT)handle_a.c

SRCS	= $(LIB_SRCS) $(PRINTF_SRCS) $(GNL_SRCS)
OBJS	= $(SRCS:.c=.o)
NAME	= libft.a

CC	= gcc
CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)

.c.o:
	@printf "[CC] %s                                                  \r" $<
	@$(CC) $(CFLAGS) -c $<  -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
