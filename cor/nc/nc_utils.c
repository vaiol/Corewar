/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isolomak <isolomak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 17:07:17 by isolomak          #+#    #+#             */
/*   Updated: 2017/06/12 17:53:46 by isolomak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	change_speed(t_data *data, int key)
{
	if (key == 'w')
		if (data->speed > 1)
			data->speed--;
	if (key == 'q')
		if (data->speed > 11)
			data->speed -= 10;
	if (key == 'e')
		data->speed++;
	if (key == 'r')
		data->speed += 10;
}

void	get_color(int pn, WINDOW *win)
{
	if (pn == 5)
		wattron(win, COLOR_PAIR(5));
	else if (pn == 1)
		wattron(win, COLOR_PAIR(1));
	else if (pn == 2)
		wattron(win, COLOR_PAIR(2));
	else if (pn == 3)
		wattron(win, COLOR_PAIR(3));
	else if (pn == 4)
		wattron(win, COLOR_PAIR(4));
}

void	get_carriage_color(int pn, WINDOW *win)
{
	if (pn == 5)
		wattron(win, COLOR_PAIR(10));
	else if (pn == 1)
		wattron(win, COLOR_PAIR(6));
	else if (pn == 2)
		wattron(win, COLOR_PAIR(7));
	else if (pn == 3)
		wattron(win, COLOR_PAIR(8));
	else if (pn == 4)
		wattron(win, COLOR_PAIR(9));
}

void	nc_refresh(t_data *data, t_print *print)
{
	nc_print_map(data, print->win_map);
	nc_print_stat(data, print->win_stat);
	wrefresh(print->win_map);
	wrefresh(print->win_stat);
}

void	shut_down_nc(t_data *data)
{
	delwin(data->print.win_corwar);
	delwin(data->print.win_map);
	delwin(data->print.win_stat);
	endwin();
	exit(1);
}
