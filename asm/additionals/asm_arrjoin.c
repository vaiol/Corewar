#include "../asm.h"

unsigned char	*asm_join(unsigned char *s1, unsigned char *s2, int l1, int l2)
{
	unsigned char	*str;
	int				i;
	int				j;

	if (!s1 || !s2)
		return (0);
	str = (unsigned char *)malloc(sizeof(unsigned char) * (l1 + l2));
	if (!str)
		return (0);
	i = 0;
	while (i < l1)
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < l2)
		str[i++] = s2[j++];
	free(s1);
	return (str);
}
