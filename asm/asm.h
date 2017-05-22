#ifndef ASM_H
# define ASM_H

# include "../libft/libft.h"
# include "../op.h"
# include <fcntl.h>


typedef struct		s_operation
{
	char			*name;
	char			**args;
	char			*label;
	int				index;
	unsigned char 	coding_string[14];
	int 			count;
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
	int 			count;
	t_operation		**ops;
}					t_file_struct;

char				**asm_read_file(char *file_name);
int					asm_compare_str(char *str, char *str2);
int					asm_skip_empty_lines(char *str, int i);
int					asm_skip_spaces(char *str, int i);
int					asm_parse_operations(char *file, int i, t_file_struct *content);
t_file_struct		*asm_parse_content_file(char *file_name);
t_file_struct		*asm_create_content();
void				asm_generate_byte_code(t_file_struct *content);
char				*asm_generate_string(char **file);
char				*asm_validate_operations(t_file_struct *content);
int					asm_is_arg(char *arg);
t_operation			*asm_create_operation(void);
char				*asm_invalid_type_message(t_operation *op, int number);
char				*asm_label_exist(t_file_struct *content, char *label);
void		asm_generate_coding_comand(t_file_struct *content);
char 		*asm_file_name(char *str, char *file_name);
int		get_label_len(t_file_struct *content, char *label, int index);
void		asm_generate_magic_proglen(t_file_struct *content, unsigned int n);
int	asm_invalid_content(t_file_struct *content);
void		asm_write(t_file_struct *content, int fd);
unsigned char	*asm_join(unsigned char *s1, unsigned char *s2, int l1, int l2);
void		asm_generate_coding_programm(t_file_struct *content);
unsigned char	asm_generate_codind_byte(t_operation *op);






void	print_op(t_operation *op);

#endif
