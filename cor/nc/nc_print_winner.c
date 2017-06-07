//
// Created by Ivan Solomakhin on 6/7/17.
//

#include "../corewar.h"

//void	create_winner_win(t_data *data)
//{
//
//}

void	nc_print_winner(t_data *data, int winner)
{
	WINDOW *win;
	WINDOW *border;
	int params[4];

//	int offset_x;
//	int offset_y;
//	int height;
//	int width;
	char *name;

	name = data->champs[winner].prog_name;
	params[0] = 20 + (ft_strlen(name));
	params[1] = 5;

	params[2] = (COLS - params[0]) / 2;
	params[3] = (LINES - params[1]) / 2;

//	width = 20 + (ft_strlen(name));
//	height = 6;
//
//	offset_x = (COLS - width) / 2;
//	offset_y = (LINES - height) / 2;

	border = newwin(params[1] + 2, params[0] + 2, params[3] - 1, params[2] - 1);
	win = newwin(params[1], params[0], params[3], params[2]);

	box(border, 0, 0);
	wmove(win, 2, (params[0] - (ft_strlen(name) + 10)) / 2);

	wprintw(win, "Winner is ");
	get_color(winner + 1, win);
	wprintw(win, "%s", name);
	refresh();
	wrefresh(border);
	wrefresh(win);

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