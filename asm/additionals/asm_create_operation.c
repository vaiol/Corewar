#include "../asm.h"

t_operation	*asm_create_operation(void)
{
	t_operation	*op;

	op = (t_operation *)malloc(sizeof(t_operation));
	op->args = NULL;
	op->label = NULL;
	op->name = NULL;
	op->index = -1;
	return (op);
}
