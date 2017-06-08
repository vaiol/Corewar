//
// Created by Ivan Solomakhin on 5/21/17.
//
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

void	nc_start(t_data *data)
{
	int quit;
	int key;

	quit = 'o';
	while (quit != 'x')
	{
		if (data->print.status == 0)
			data->print.status = 1;
		timeout(data->speed);
		key = getch();
		if (key == 'x')
			quit = key;
		else if (key == ' ')
			nc_pause(data);
		else if (key == 'q' || key == 'w' || key == 'e' || key == 'r')
			change_speed(data, key);
		manage_corewar(data);
		nc_refresh(data, &data->print);
	}
	shut_down_nc(data);
}

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
	if (key == 'x')
		shut_down_nc(data);
	else if (key == ' ')
		nc_start(data);
	else if (key == 'q' || key == 'w' || key == 'e' || key == 'r')
	{
		change_speed(data, key);
		nc_refresh(data, &data->print);
		nc_pause(data);
	}
	else
		nc_pause(data);
}

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

void	nc_prepare(t_data *data, t_print *print)
{
	int offset_x;
	int offset_y;
	int height;
	int width;

	width = 300;
	height = 76;
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

void	init_ncurses(t_data *data, t_print *print)
{
	char *title;

	title = "CoreWar v. 1.1  -  Press 'space' to start/pause. Press 'x' to quit.";
	initscr();
	if (COLS < 361 || LINES < 87)
	{
		ft_printf("Error : Please use terminal in full screen mode for -v flag\n");
		endwin();
		exit(1);
	}
	noecho();
	curs_set(FALSE);
	cbreak();
	start_color();
	init_colors();
	move(3, (COLS - ft_strlen(title)) / 2);
	printw("%s", title);
	refresh();
	nc_prepare(data, print);
	nc_pause(data);
}