#include "../asm.h"

char		*asm_label_exist(t_file_struct *content, char *label)
{
	char	*err;
	int		i;

	if (label[0] == DIRECT_CHAR)
		label = label + 2;
	else
		label = label + 1;
	err = NULL;
	i = 0;
	while (content->ops[i])
	{
		if (ft_strequ(content->ops[i]->label, label))
			return (err);
		i++;
	}
	err = ft_strjoin("No such label ", label);
	return (err);
}

