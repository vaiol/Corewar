#include "corewar.h"

void	error_handler(char *str)
{
	ft_printf("%s\n", str);
	exit(1);
}

void	champ_error_handler(char *str, char *champion)
{
	ft_printf("Error : %s %s\n", champion, str);
	exit(1);
}

void 	error_handler_usage(void)
{
	ft_printf("usage: corewar [-alv] [file ...]\n");
	exit(1);
}