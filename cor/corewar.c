
#include "corewar.h"

void	init_colors(void)
{
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);

	init_pair(6, COLOR_BLACK, COLOR_GREEN);
	init_pair(7, COLOR_BLACK,  COLOR_BLUE);
	init_pair(8, COLOR_BLACK, COLOR_RED);
	init_pair(9, COLOR_BLACK, COLOR_CYAN);
	init_pair(10, COLOR_BLACK, COLOR_WHITE);
}

void	nc_print_stat(t_data *data, WINDOW *win)
{

	char *status;

	wclear(win);
	if (data->print.status == 0)
		status = "PAUSED";
	else
		status = "RUNNING";

	wmove(win, 3, 50 - ((ft_strlen(status) + 7) / 2));
	wprintw(win, "Status : ", status);
	if (data->print.status == 0)
		wattron(win, COLOR_PAIR(3));
	else
		wattron(win, COLOR_PAIR(1));
	wprintw(win, "%s", status);



	wattroff(win, COLOR_PAIR(5));
	wmove(win, 5, 50 - (ft_strlen("Cycle :    ") / 2));
	wprintw(win, "Cycle : %i", data->print.cycle);
}

void	nc_print_map(t_data *data, WINDOW *win)
{
	int i;
	int x;
	int y;

	i = 0;
	x = 1;

	y = 3;

	wclear(win);
	wmove(win, 3, 3);

	while (i < MEM_SIZE)
	{
		if (data->map[i].pn == 5)
		{
			wattron(win, COLOR_PAIR(5));
			if (data->map[i].carriage == 1)
				wattron(win, COLOR_PAIR(10));
		}
		else if (data->map[i].pn == 0)
		{
			wattron(win, COLOR_PAIR(1));
			if (data->map[i].carriage == 1)
				wattron(win, COLOR_PAIR(6));
		}
		else if (data->map[i].pn == 1)
		{
			wattron(win, COLOR_PAIR(2));
			if (data->map[i].carriage == 1)
				wattron(win, COLOR_PAIR(7));
		}
		else if (data->map[i].pn == 2)
		{
			wattron(win, COLOR_PAIR(3));
			if (data->map[i].carriage == 1)
				wattron(win, COLOR_PAIR(8));
		}
		else if (data->map[i].pn == 3)
		{
			wattron(win, COLOR_PAIR(4));
			if (data->map[i].carriage == 1)
				wattron(win, COLOR_PAIR(9));
		}

		wprintw(win, "%02x", data->map[i].cell);
		wattron(win, COLOR_PAIR(5));
		wprintw(win, " ");

		if (x >= 64)
		{
			wprintw(win, "\n");
			y++;
			x = 0;
			wmove(win, y, 3);
		}
		x++;
		i++;
	}
}

void	init_ncurses(t_data *data, t_print *print)
{
	int offset_x;
	int offset_y;
	int height;
	int width;

	width = 300;
	height = 76;

	initscr();
	noecho();
	curs_set(FALSE);
	cbreak();
	start_color();

	init_colors();

	printw("CoreWar v. 0.1  -  Press 'space' to start/pause. Press 'q' to quit...");

	refresh();

	offset_x = (COLS - width) / 2;
	offset_y = (LINES - height) / 2;

	print->win_corwar = newwin(height, width, offset_y, offset_x); // h, w, oy, ox;
	print->win_map = newwin(height - 8, width - 104, offset_y + 3, offset_x + 2);
	print->win_stat = newwin(height - 4, 100, offset_y + 2, offset_x + 198);

	box(print->win_corwar, 0, 0);

	nc_print_map(data, print->win_map);
	nc_print_stat(data, print->win_stat);

	refresh();
	wrefresh(print->win_corwar);
	wrefresh(print->win_map);
	wrefresh(print->win_stat);
}

void	shut_down_nc(t_data *data)
{
	delwin(data->print.win_corwar);
	delwin(data->print.win_map);
	delwin(data->print.win_stat);
	endwin();
}

void	nc_refresh(t_data *data, t_print *print)
{

	data->print.cycle++;

	nc_print_map(data, print->win_map);
	nc_print_stat(data, print->win_stat);
	wrefresh(print->win_map);
	wrefresh(print->win_stat);
}

//

void	nc_pause(t_data *data)
{
	int key;

	if (data->print.status == 1)
	{
		data->print.status = 0;
		nc_print_stat(data, data->print.win_stat);
		wrefresh(data->print.win_stat);
	}
	key = getch();

	if (key == 'q')
		shut_down_nc(data);
	else if (key == ' ')
		nc_start(data);
	else
		nc_pause(data);
}

void	manage_corewar(t_data *data)
{
	int n;

	n = 0;
	while (n < data->count)
	{
		data->map[data->champs[n].carriage->index].carriage = 0;
		if (data->champs[n].carriage->index >= MEM_SIZE)
			data->champs[n].carriage->index = -1;
		data->champs[n].carriage->index++;
		data->map[data->champs[n].carriage->index].carriage = 1;
		n++;
	}
}

void	nc_start(t_data *data)
{
	int quit;
	int change_status;
	int key;

	quit = 'o';
	change_status = '0';

	while (quit != 'q')
	{
		if (data->print.status == 0)
			data->print.status = 1;
		timeout(100);
		key = getch();
		if (key == 'q')
			quit = key;
		else if (key == ' ')
			nc_pause(data);
//
		manage_corewar(data);
//
		nc_refresh(data, &data->print);
	}
	shut_down_nc(data);
}

void	corewar(t_data *data)
{
	if (data->fl.flags > 0)
	{
		if (data->fl.n == 1)
		{
			init_ncurses(data, &data->print);
			nc_pause(data);
		}
	}
	else
	{
		//	for testing
		print_map(data);
	}
}