#include "../asm.h"

static char	*ft_strj(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (0);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (0);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = '\n';
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	free(s2);
	return (str);
}

char		*asm_generate_string(char **file)
{
	char *str;
	int i;

	i = 0;
	str = ft_strdup("");
	while (file && file[i])
	{
		str = ft_strj(str, file[i]);
		i++;
	}
	free(file);
	return (str);
}
