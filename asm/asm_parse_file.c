#include "asm.h"

static int		validation(char *file, t_file_struct *content)
{
	int	i;

	i = asm_validate_name(file, 0, content);
	if (i == -1)
		return (-1);
	i = asm_validate_name(file, i, content);
	if (i == -1)
		return (-1);
	return (i);
}

t_file_struct	*asm_parse_content_file(char *file_name)
{
	t_file_struct	*content;
	char			**file;
	char 			*str;
	int i;


	if (!(file = asm_read_file(file_name)))
		return (NULL);
	str = asm_generate_string(file);
	content = asm_create_content();
	i = validation(str, content);
	if (i < 0)
		return (NULL);
	return (content);
}