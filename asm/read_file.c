#include "asm.h"

static char		**remove_comments(char **file)
{
	int	i;
	int j;

	if (file == NULL)
		return (NULL);
	i = 0;
	while(file[i])
	{
		j = 0;
		while (file[i][j])
		{
			if (file[i][j] == '#')
			{
				file[i][j] = '\0';
				break ;
			}
			j++;
		}
		i++;
	}
	return (file);
}

char			**read_file(char *file_name)
{
	char	**result;
	char	*file_content;
	off_t	size;
	int		fd;

	if ((fd = open(file_name, O_RDONLY)) == -1)
	{
		ft_printf("%s: cannot open file.\n");
		return (NULL);
	}
	size = lseek(fd, 0, SEEK_END);
	if (size < 0)
	{
		ft_printf("%s: file is not valid.\n");
		return (NULL);
	}
	file_content = (char *)malloc(sizeof(char) * (size + 1));
	read(fd, file_content, (size_t)size);
	file_content[size] = '\0';
	result = ft_strsplit(file_content, '\n');
	free(file_content);
	return (remove_comments(result));
}