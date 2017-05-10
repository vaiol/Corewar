#ifndef ASM_H
# define ASM_H

# include "../libft/libft.h"
# include "../op.h"
# include <fcntl.h>



char			**asm_read_file(char *file_name);





int				asm_compare_str(char *str, char *str2);
int				asm_skip_empty_lines(char *str, int i);
int				asm_skip_spaces(char *str, int i);
int				asm_validate_name(char *file, int i, t_file_struct *content);

t_file_struct	*asm_parse_content_file(char *file_name);
t_file_struct	*asm_create_content();

void			asm_generate_byte_code(t_file_struct *content);

char			*asm_generate_string(char **file);







#endif
