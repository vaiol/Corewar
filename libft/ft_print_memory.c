/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 11:03:07 by exam              #+#    #+#             */
/*   Updated: 2017/02/13 15:41:57 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putchar_hex(const unsigned char c)
{
	if (c >= ' ' && c <= '~')
		write(1, &c, 1);
	else
		write(1, ".", 1);
}

static void	ft_putnbr_hex(const unsigned char nbr, int rm)
{
	char	*base;

	base = "0123456789abcdef";
	if (rm > 0)
		ft_putnbr_hex(nbr / 16, rm - 1);
	write(1, &(base[nbr % 16]), 1);
}

static void	ft_print_symbols(const unsigned char *adr, size_t i, size_t size)
{
	size_t	a;

	a = 0;
	while (a < 16 && i < size)
	{
		ft_putchar_hex(adr[i]);
		a++;
		i++;
	}
}

void		ft_print_memory(const void *addr, size_t size)
{
	unsigned char	*adr;
	size_t			i;

	adr = (unsigned char *)addr;
	i = 0;
	while (i < (size) || i % 16)
	{
		if (i % 2 == 0 && i != 0)
			write(1, " ", 1);
		if (i < size && i % 16 == 0 && i != 0)
		{
			ft_print_symbols(adr, i - 16, size);
			write(1, "\n", 1);
		}
		if (i < size)
			ft_putnbr_hex(adr[i], 1);
		else
			write(1, "  ", 2);
		i++;
	}
	write(1, " ", 1);
	ft_print_symbols(adr, i - 16, size);
	write(1, "\n", 1);
}
