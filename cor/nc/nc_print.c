//
// Created by Ivan Solomakhin on 5/21/17.
//

#include "../corewar.h"

void	print_cell(unsigned char cell, WINDOW *win)
{
	wprintw(win, "%02x", cell);
	wattron(win, COLOR_PAIR(5));
	wprintw(win, " ");
}

void	nc_print_map(t_data *data, WINDOW *win)
{
	int i;
	int x;
	int y;

	i = -1;
	x = 1;
	y = 3;
	wmove(win, 3, 3);
	while (++i < MEM_SIZE)
	{
		if (data->map[i].carriage == 1)
			get_carriage_color(data->map[i].pn, win);
		else
			get_color(data->map[i].pn, win);
		print_cell(data->map[i].cell, win);
		if (x >= 64)
		{
			x = 0;
			y++;
			wmove(win, y, 3);
		}
		x++;
	}
}

void	nc_print_stat(t_data *data, WINDOW *win)
{
	print_stat_status(data, win);
	print_stat_cycle(data, win);
	print_num_processes(data, win);
	print_champs(data, win);
	print_rules(data, win);
}
