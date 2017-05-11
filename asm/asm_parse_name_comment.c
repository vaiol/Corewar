#include "asm.h"

static int 	get_name(char *file, int i, t_file_struct *content, int flag)
{
	int j;

	i = asm_skip_spaces(file, i);
	if (file[i] == '"')
	{
		i++;
		j = 0;
		while (file[i + j] && file[i + j] != '"')
			j++;
		if (flag)
			content->comment = ft_strsub(file, (unsigned)i, (size_t)j);
		else
			content->prog_name = ft_strsub(file, (unsigned)i, (size_t)j);
		return (i + j + 1);
	}
	else
		return (-1);

}
int		asm_validate_name(char *file, int i, t_file_struct *content)
{
	int		j;

	i = asm_skip_empty_lines(file, i);
	if ((j = asm_compare_str(file + i, NAME_CMD_STRING)))
		return (get_name(file, i + j, content, 0));
	else if ((j = asm_compare_str(file + i, COMMENT_CMD_STRING)))
		return (get_name(file, i + j, content, 1));
	return (i);
}
