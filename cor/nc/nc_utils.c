//
// Created by Ivan Solomakhin on 5/21/17.
//

#include "../corewar.h"

void	get_color(int pn, WINDOW *win)
{
	if (pn == 5)
		wattron(win, COLOR_PAIR(5));
	else if (pn == 0)
		wattron(win, COLOR_PAIR(1));
	else if (pn == 1)
		wattron(win, COLOR_PAIR(2));
	else if (pn == 2)
		wattron(win, COLOR_PAIR(3));
	else if (pn == 3)
		wattron(win, COLOR_PAIR(4));
}

void	get_carriage_color(int pn, WINDOW *win)
{
	if (pn == 5)
		wattron(win, COLOR_PAIR(10));
	else if (pn == 0)
		wattron(win, COLOR_PAIR(6));
	else if (pn == 1)
		wattron(win, COLOR_PAIR(7));
	else if (pn == 2)
		wattron(win, COLOR_PAIR(8));
	else if (pn == 3)
		wattron(win, COLOR_PAIR(9));
}

void	nc_refresh(t_data *data, t_print *print)
{
	data->print.cycle++;
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
