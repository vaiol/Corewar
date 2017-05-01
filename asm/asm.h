#ifndef ASM_H
# define ASM_H

# include "../libft/libft.h"
# include <fcntl.h>

typedef struct	s_flag
{
	int			name;
	int			comment;

}				t_flag;
t_flag			g_flag;

char	**read_file(char *file_name);



#endif
