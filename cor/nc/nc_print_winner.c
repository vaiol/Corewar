/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nc_print_winner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 17:52:29 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:52:44 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	winner_loop(t_data *data)
{
	int quit;
	int key;

	quit = 'o';
	while (quit != 'x')
	{
		key = getch();
		if (key == 'x')
			quit = key;
	}
	shut_down_nc(data);
}

void	nc_print_winner(t_data *data, t_print *p, int winner)
{
	int		prms[4];
	char	*name;

	name = data->champs[winner].prog_name;
	prms[0] = 20 + ((int)ft_strlen(name));
	prms[1] = 5;
	prms[2] = (COLS - prms[0]) / 2;
	prms[3] = (LINES - prms[1]) / 2;
	p->border = newwin(prms[1] + 2, prms[0] + 2, prms[3] - 1, prms[2] - 1);
	p->win = newwin(prms[1], prms[0], prms[3], prms[2]);
	box(p->border, 0, 0);
	wmove(p->win, 2, (prms[0] - ((int)ft_strlen(name) + 10)) / 2);
	wprintw(p->win, "Winner is ");
	get_color(winner + 1, p->win);
	wprintw(p->win, "%s", name);
	refresh();
	wrefresh(p->border);
	wrefresh(p->win);
	winner_loop(data);
}
