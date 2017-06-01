#include "../asm.h"

int		asm_get_line(int index, char *file)
{
	int i;
	int	line;

	i = 0;
	line = 0;
	while (file[i] && i < index)
	{
		if (file[i] == '\n')
			line++;
		i++;
	}
	return (line);
}

int		asm_get_place(int index, char *file)
{
	int i;
	int	place;

	i = 0;
	place = 1;
	while (file[i] && i < index)
	{
		if (file[i] == '\n')
			place = 0;
		place++;
		i++;
	}
	return (place);
}

