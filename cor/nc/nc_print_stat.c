//
// Created by Ivan Solomakhin on 5/21/17.
//

#include "../corewar.h"

void	print_stat_status(t_data *data, WINDOW *win)
{
	char *status;

	if (data->print.status == 0)
		status = "PAUSED";
	else
		status = "RUNNING";

	wmove(win, 6, 50 - ((ft_strlen(status) + 7) / 2));
	if (data->print.status == 0)
	{
		wprintw(win, "Status : ", status);
		wattron(win, COLOR_PAIR(3));
	}
	else
	{
		wprintw(win, " Status : ", status);
		wattron(win, COLOR_PAIR(1));
	}
	wprintw(win, "%s ", status);
	wattroff(win, COLOR_PAIR(5));
}

void	print_stat_cycle(t_data *data, WINDOW *win)
{
	wmove(win, 12, 50 - (ft_strlen("Info") / 2));
	wprintw(win, " Info");
	wmove(win, 14, 50 - (ft_strlen("Cycle :    ") / 2));
	wprintw(win, "Cycle : %i", data->print.cycle);
}

void	print_num_processes(t_data *data, WINDOW *win)
{
	int		n;
	int		processes;
	t_carr *current;

	processes = 0;
	n = -1;
	while (++n < data->count)
	{
		current = data->champs[n].carriage;
		while (current != NULL)
		{
			processes++;
			current = current->next;
		}
	}
	wmove(win, 16, 50 - ((ft_strlen("Processes :") + 8 ) / 2));
	wprintw(win, "Processes : %i", processes);
}

void	print_champs(t_data *data, WINDOW *win)
{
	int n;
	int width;
	int height;

	height = 24;
	wmove(win, height - 2, 50 - ft_strlen("Players") / 2);
	wprintw(win, " Players");

	n = -1;
	while (++n < data->count)
	{
		width = 50 - ((ft_strlen(data->champs[n].prog_name) + 13) / 2);
		wmove(win, height, width);
		wprintw(win, "Player %i : ", n + 1);
		get_color(n, win);
		wprintw(win, "%s", data->champs[n].prog_name);
		wattroff(win, COLOR_PAIR(5));
		height += 2;
	}
}

void	print_rules(t_data *data, WINDOW *win)
{
	wmove(win, 35, 50 - ft_strlen("Rules") / 2);
	wprintw(win, " Rules");
	wmove(win, 37, 50 - (ft_strlen("Cycle To Die") / 2) - 6);
	wprintw(win, "Cycle To Die : %i", data->print.cycle_to_die);
	wmove(win, 39, 50 - (ft_strlen("Cycle Delta") / 2) - 6);
	wprintw(win, "Cycle Delta : %i", CYCLE_DELTA);
	wmove(win, 41, 50 - (ft_strlen("Nbr Live") / 2) - 4);
	wprintw(win, "Nbr Live : %i", NBR_LIVE);
	wmove(win, 43, 50 - (ft_strlen("Max Checks") / 2) - 5);
	wprintw(win, "Max Checks : %i", MAX_CHECKS);
}
