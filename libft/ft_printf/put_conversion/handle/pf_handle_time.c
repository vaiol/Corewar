/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_handle_time.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astepano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 19:54:16 by astepano          #+#    #+#             */
/*   Updated: 2017/04/02 19:54:18 by astepano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pf_handle.h"

static int		leapyear(int year)
{
	return (!((year) % 4) && (((year) % 100) || !((year) % 400)));
}

static int		yearsize(int year)
{
	if (leapyear(year))
		return (366);
	return (365);
}

static int		**create_ytab(void)
{
	int	**ytab;
	int	i;

	ytab = (int **)malloc(sizeof(int *) * 2);
	ytab[0] = (int *)malloc(sizeof(int) * 12);
	ytab[0][0] = 31;
	ytab[0][1] = 28;
	ytab[0][2] = 31;
	ytab[0][3] = 30;
	ytab[0][4] = 31;
	ytab[0][5] = 30;
	ytab[0][6] = 31;
	ytab[0][7] = 31;
	ytab[0][8] = 30;
	ytab[0][9] = 31;
	ytab[0][10] = 30;
	ytab[0][11] = 31;
	ytab[1] = (int *)malloc(sizeof(int) * 12);
	i = -1;
	while (++i < 12)
		ytab[1][i] = ytab[0][i];
	ytab[1][1] = 29;
	return (ytab);
}

t_time			*pf_handle_time(const unsigned long long time)
{
	t_time		*stime;
	long long	dayclock;
	int			**ytab;

	ytab = create_ytab();
	stime = (t_time *)(malloc(sizeof(t_time)));
	dayclock = time % (24 * 60 * 60);
	stime->day = time / (24 * 60 * 60);
	stime->year = 1970;
	stime->sec = dayclock % 60;
	stime->min = (dayclock % 3600) / 60;
	stime->hour = dayclock / 3600;
	while (stime->day >= yearsize(stime->year))
		stime->day -= yearsize(stime->year++);
	stime->month = 0;
	while (stime->day >= ytab[leapyear(stime->year)][stime->month])
		stime->day -= ytab[leapyear(stime->year)][stime->month++];
	stime->month = stime->month + 1;
	stime->day++;
	free(ytab);
	return (stime);
}

char			*pf_create_time(char *t1, int n2, char *delim)
{
	char *result;
	char *t2;
	char *tmp;

	t2 = ft_itoa_base(n2, 10);
	if (ft_strlen(t2) < 2)
		delim = ft_strjoin(delim, "0");
	tmp = t2;
	t2 = ft_strjoin(delim, t2);
	result = ft_strjoin(t1, t2);
	free(tmp);
	free(t1);
	free(t2);
	return (result);
}
