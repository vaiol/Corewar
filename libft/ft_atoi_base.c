#include "libft.h"

static int	ft_atoi_str_base(const char *str, const int base)
{
	int		num;
	int		res;

	num = 0;
	res = 0;
	while (ft_isdigit(*str) || (*str >= 'A' && *str <= ('A' + base - 10)))
	{
		num = (*str >= '0' && *str <= '9') ? *str - '0' : *str - 55;
		res = res * base + num;
		str++;
	}
	return (res);
}

int			ft_atoi_base(const char *str, const int base)
{
	int		res;
	char	sign;

	res = 0;
	sign = '\0';
	if (base < 2 || base > 16 || !str)
		return (0);
	while (*str < 33)
		str++;
	if (*str == '+' || *str == '-')
		sign = *str++;
	if (base < 11)
		while (*str >= '0' && *str <= (47 + base))
			res = res * base + *str++ - '0';
	else
		res = ft_atoi_str_base(str, base);
	if (sign == '-' && base == 10)
		return (-res);
	else
		return (res);
}