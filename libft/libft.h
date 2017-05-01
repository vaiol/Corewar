/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 16:46:29 by astepano          #+#    #+#             */
/*   Updated: 2017/02/13 15:32:33 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIBFT_H
# define FT_LIBFT_H

# define BUFF_SIZE 4096
# define ABS(x)  ( (x<0) ? -(x) : (x) )

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <wchar.h>

typedef enum	e_free
{
	NONE,
	FIRST,
	SECOND,
	BOTH
}				t_free;

void			*ft_memset(void *b, int c, size_t len);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_strchr(const char *s, int c);
int				ft_strichr(char *str, char chr);
int				ft_strcchr(const char *str, char c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *big, const char *little);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_arrdel(char **arr);
int				ft_strequ(char const *s1, char const *s2);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strfjoin(char *s1, char *s2, t_free f);
char			*ft_strtrim(char const *s);
char			*ft_strcut(char *str, int max_len);
char			**ft_strsplit(char const *s, char c);
char			*ft_itoa_base(long long value, int base);
int				ft_atoi(const char *str);
double			ft_pow(double base, double ex);
void			ft_print_memory(const void *addr, size_t size);
int				ft_printf(const char *restrict format, ...);
int				get_next_line(const int fd, char **line);
char			*ft_readfd(int fd);

#endif
