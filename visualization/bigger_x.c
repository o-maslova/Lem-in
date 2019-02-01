#include "view.h"

void	first_y_bigger_2(t_win *win, int *first, int *second, int color)
{
	int tmp[2];
	int tmp_2[2];

	// dprintf(my_fd, "BIGGER_X BIGGER_Y\n");
	first[0] += (CELL_SIZE - 1) / 2;
	first[1] += (CELL_SIZE - 1) / 2;
	tmp[0] = first[0] + CELL_SIZE;
	tmp[1] = first[1];
	brznh_algo(win, tmp, first, color);
	tmp_2[0] = tmp[0];
	tmp_2[1] = second[1] - CELL_SIZE;
	brznh_algo(win, tmp, tmp_2, color);
	tmp[0] = second[0];
	tmp[1] = tmp_2[1];
	brznh_algo(win, tmp_2, tmp, color);
	brznh_algo(win, tmp, second, color);
}

void	first_y_smaller_2(t_win *win, int *first, int *second, int color)
{
	int tmp[2];

	tmp[0] = first[0];
	tmp[1] = second[1];
	brznh_algo(win, tmp, first, color);
	brznh_algo(win, tmp, second, color);
}

void	bigger_x(t_win *win, int *first, int *second, int color)
{
	// dprintf(my_fd, "BIGGER_X\n");
	// change_value(win, &first, &second);
	if (first[1] == second[1])
	{
		brznh_algo(win, first, second, color);
		// if (win->flag)
		// 	brznh_algo(win, first, second, color);
		return ;
	}
	if (first[1] < second[1])
	{
		// dprintf(my_fd, "BIGGER_X SMALLER_Y\n");
		first_y_smaller_2(win, first, second, color);
		// if (win->flag)
		// 	first_y_smaller_2(win, first, second, color);
	}
	else
	{
		// dprintf(my_fd, "BIGGER_X BIGGER_Y\n");
		first_y_bigger_2(win, first, second, color);
		// if (win->flag)
		// 	first_y_bigger_2(win, first, second, color);
	}
}
//dprintf(my_fd, "start draw new pixels with color %d\n", color);