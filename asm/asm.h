#ifndef ASM_H
# define ASM_H

# include "../libft/libft.h"
# include <fcntl.h>


typedef struct	s_argument
{
	
}				t_argument;

typedef struct	s_operation
{
	int			opcode;
	char		*name;

}				t_operation;

typedef struct	s_info
{
	char 		*name;
	char 		*comment;
	t_operation	*operations;


}				t_info;
t_info			g_info;

char	**read_file(char *file_name);





#endif
