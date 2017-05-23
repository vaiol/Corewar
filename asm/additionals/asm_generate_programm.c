#include "../asm.h"

void		asm_generate_programm(t_file_struct *content)
{
	int i;

	i = 0;
	content->coding_string = (unsigned char *)malloc(sizeof(unsigned char));
	content->count = 0;
	while (content->ops[i])
	{
		content->coding_string = asm_join(content->coding_string,
										  content->ops[i]->coding_string,
										  content->count,
										  content->ops[i]->count);
		content->count += content->ops[i]->count;
		i++;
	}
}