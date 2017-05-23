#include "../asm.h"

void	asm_get_magic(t_file_struct *content, unsigned int n)
{
	content->magic[0] = (n >> 24) & 0xFF;
	content->magic[1] = (n >> 16) & 0xFF;
	content->magic[2] = (n >> 8) & 0xFF;
	content->magic[3] = n & 0xFF;
}
