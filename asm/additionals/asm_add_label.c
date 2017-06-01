#include "../asm.h"

void	asm_add_label(t_operation *op, char *label)
{
	char	**new_labels;
	int		i;

	i = 0;
	while (op->label && op->label[i])
		i++;
	new_labels = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (op->label && op->label[i])
	{
		new_labels[i] = op->label[i];
		i++;
	}
	new_labels[i++] = label;
	new_labels[i] = NULL;
	if (op->label)
		free(op->label);
	op->label = new_labels;
}
