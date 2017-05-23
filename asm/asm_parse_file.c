#include "asm.h"

static int		get_name(char *file, int i, t_file_struct *content, int flag)
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

static int		parse_name_comment(char *file, int i, t_file_struct *content)
{
	int	j;

	i = asm_skip_empty_lines(file, i);
	if ((j = asm_compare_str(file + i, NAME_CMD_STRING)))
		return (get_name(file, i + j, content, 0));
	else if ((j = asm_compare_str(file + i, COMMENT_CMD_STRING)))
		return (get_name(file, i + j, content, 1));
	return (i);
}

static int 		validate_name_comment(t_file_struct *content)
{
	if(ft_strlen(content->prog_name) > PROG_NAME_LENGTH)
	{
		ft_printf("ERROR\n");
		return (0);
	}
	if(ft_strlen(content->comment) > COMMENT_LENGTH)
	{
		ft_printf("ERROR\n");
		return (0);
	}
	return (1);

}

static int		validation(char *file, t_file_struct *content)
{
	int	i;

	i = parse_name_comment(file, 0, content);
	if (i == -1)
		return (-1);
	i = parse_name_comment(file, i, content);
	if (i == -1)
		return (-1);
	if (!validate_name_comment(content))
		return (-1);
	i = asm_parse_operations(file, i, content);
	if (i == -1)
		return (-1);
	return (i);
}


t_file_struct	*asm_parse_content_file(char *file_name)
{
	t_file_struct	*content;
	char			**file;
	char 			*str;
	int				i;


	if (!(file = asm_read_file(file_name)))
		return (NULL);
	str = asm_generate_string(file);
	content = asm_create_content();
	content->file_name = asm_file_name(content->file_name, file_name);
	i = validation(str, content);
	if (i < 0)
		return (NULL);
	return (content);
}