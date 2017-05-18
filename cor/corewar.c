
#include "corewar.h"

//void	nc_print_map(t_data *data)
//{
//	int i;
//	int x;
//
//	i = 0;
//	x = 1;
//
//	init_pair(1, COLOR_GREEN, COLOR_BLACK);
//	init_pair(2, COLOR_BLUE, COLOR_BLACK);
//	init_pair(3, COLOR_RED, COLOR_BLACK);
//	init_pair(4, COLOR_CYAN, COLOR_BLACK);
//	init_pair(5, COLOR_WHITE, COLOR_BLACK);
//
//	init_pair(6, COLOR_BLACK, COLOR_GREEN);
//	init_pair(7, COLOR_BLACK,  COLOR_BLUE);
//	init_pair(8, COLOR_BLACK, COLOR_RED);
//	init_pair(9, COLOR_BLACK, COLOR_CYAN);
//	init_pair(10, COLOR_BLACK, COLOR_WHITE);
//
//	while (i < MEM_SIZE)
//	{
//		if (data->map[i].pn == 5)
//		{
//			attron(COLOR_PAIR(5));
//			if (data->map[i].carriage == 1)
//				attron(COLOR_PAIR(10));
//		}
//		else if (data->map[i].pn == 0)
//		{
//			attron(COLOR_PAIR(1));
//			if (data->map[i].carriage == 1)
//				attron(COLOR_PAIR(6));
//		}
//		else if (data->map[i].pn == 1)
//		{
//			attron(COLOR_PAIR(2));
//			if (data->map[i].carriage == 1)
//				attron(COLOR_PAIR(7));
//		}
//		else if (data->map[i].pn == 2)
//		{
//			attron(COLOR_PAIR(3));
//			if (data->map[i].carriage == 1)
//				attron(COLOR_PAIR(8));
//		}
//		else if (data->map[i].pn == 3)
//		{
//			attron(COLOR_PAIR(4));
//			if (data->map[i].carriage == 1)
//				attron(COLOR_PAIR(9));
//		}
//
//		printw("%02x", data->map[i].cell);
//		attron(COLOR_PAIR(5));
//		printw(" ");
//
//		if (x >= 64)
//		{
//			printw("\n");
//			x = 0;
//		}
//		x++;
//		i++;
//	}
//}

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

void	nc_print_map(t_data *data, WINDOW *win)
{
	int i;
	int x;
	int y;

	i = 0;
	x = 1;

	y = 3;

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

void	init_ncurses(t_data *data)
{
	WINDOW *win_corwar;
	WINDOW *win_map;
	WINDOW *win_map_cont;

	int offset_x;
	int offset_y;
	int height;
	int width;

	width = 300;
	height = 76;

	initscr();
	noecho();
	cbreak();
	start_color();

	init_colors();

	printw("CoreWar v. 0.1  -  Press x to quit...");

	refresh();

	offset_x = (COLS - width) / 2;
	offset_y = (LINES - height) / 2;

	win_corwar = newwin(height, width, offset_y, offset_x); // h, w, oy, ox;
	win_map = newwin(height - 4, width - 100, offset_y + 2, offset_x + 1);
	win_map_cont = newwin(height - 8, width - 104, offset_y + 3, offset_x + 2);

//	win_corwar = newwin(height, width, 5, 0); // h, w, oy, ox;
//	win_map = newwin(height - 4, width - 100, 7, 1);
//	win_map_cont = newwin(height - 8, width - 104, 8, 2);

	box(win_corwar, 0, 0);
	box(win_map, 0, 0);
//	box(win_map_cont, 0, 0);

	nc_print_map(data, win_map_cont);

	refresh();
	wrefresh(win_corwar);
	wrefresh(win_map);
	wrefresh(win_map_cont);

	getch(); // ждём нажатия символа

	delwin(win_corwar);
	delwin(win_map);
	delwin(win_map_cont);

	endwin(); // завершение работы с ncurses
}

//void	init_ncurses(t_data *data)
//{
//	initscr();
//	noecho();
//	start_color();
//
//	nc_print_map(data);
//
//	move(0, 0); // y, x
//
////	printw("Hello world !!!");
//	refresh(); // обновить
//	getch(); // ждём нажатия символа
//	endwin(); // завершение работы с ncurses
//}


void	corewar(t_data *data)
{
	if (data->fl.flags > 0)
	{
		if (data->fl.n == 1)
		{
			init_ncurses(data);
//			init_ncurses();
		}
	}
	else
	{
		//	for testing
		print_map(data);
	}
}