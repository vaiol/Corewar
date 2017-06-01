/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 15:11:36 by astepano          #+#    #+#             */
/*   Updated: 2017/05/24 15:28:30 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# define MSG_NAME_COMMENT "Syntax error: name or comment invalid\n"
# define MSG_PROG_NAME "prog name length error\n"
# define MSG_COMMENT "comment length error\n"
# define MSG_COMPLETE "Writing output program to %s\n"
# define MSG_ERR_FILE "Can't create or open %s\n"
# define MSG_SYNTAX "Syntax error at token [TOKEN]"
# define MSG_LEXICAL "Lexical error at "
# define MSG_DIR "DIRECTION"
# define MSG_INDIR "INDIRECTION"
# define MSG_REG "REGISTER"
# include "../libft/libft.h"
# include "../op.h"
# include <fcntl.h>

typedef enum		e_err_type
{
	LEXICAL,
	SYNTAX
}					t_err_type;

typedef struct		s_operation
{
	char			*name;
	char			**args;
	char			**label;
	int				index;
	unsigned char	coding_string[14];
	int				count;
	int				len;
}					t_operation;

typedef struct		s_file_struct
{
	unsigned int	magic[4];
	char			*prog_name;
	unsigned int	prog_size;
	char			*comment;
	char			*file_name;
	unsigned char	*coding_string;
	int				count;
	t_operation		**ops;
	t_err_type		err_type;
	int				err_index;
}					t_file_struct;

char				**asm_read_file(char *file_name);
int					asm_compare_str(char *str, char *str2);
int					asm_skip_empty_lines(char *str, int i);
int					asm_skip_spaces(char *str, int i);
int					asm_parse_operations(char *file, int i,
		t_file_struct *content);
t_file_struct		*asm_parse_content_file(char *file_name);
t_file_struct		*asm_create_content(void);
void				asm_generate_byte_code(t_file_struct *content);
char				*asm_generate_string(char **file);
char				*asm_validate_operations(t_file_struct *content);
int					asm_is_arg(char *arg);
t_operation			*asm_create_operation(void);
char				*asm_invalid_type_message(t_operation *op, int number);
char				*asm_label_exist(t_file_struct *content, char *label);
void				asm_generate_byte_ops(t_file_struct *f);
char				*asm_file_name(char *str, char *file_name);
int					asm_label_len(t_file_struct *content,
		char *label, int index);
void				asm_get_magic(t_file_struct *content, unsigned int n);
int					asm_validate_content(t_file_struct *content);
unsigned char		*asm_join(unsigned char *s1, unsigned char *s2,
		int l1, int l2);
void				asm_get_prog_len(t_file_struct *content);
int					asm_get_line(int index, char *file);
int					asm_get_place(int index, char *file);
void				asm_add_label(t_operation *op, char *label);

#endif
