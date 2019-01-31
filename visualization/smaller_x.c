#include "view.h"

void	first_y_bigger_1(t_win *win, t_dot first, t_dot second, int color)
{
	t_dot tmp;
	t_dot tmp_2;

	tmp.x = first.x;
	tmp.y = first.y + CELL_SIZE;
	brznh_algo(win, tmp, first, color);
	brznh_algo(win, tmp, first, color);
	tmp_2.x = second.x;
	tmp_2.y = tmp.y;
	brznh_algo(win, tmp, tmp_2, color);
	brznh_algo(win, tmp_2, second, color);
}

void	first_y_smaller_1(t_win *win, t_dot first, t_dot second, int color)
{
	t_dot tmp;
	t_dot tmp_2;

	tmp.x = first.x;
	tmp.y = second.y + CELL_SIZE;
	brznh_algo(win, tmp, first, color);
	brznh_algo(win, tmp, first, color);
	tmp_2.x = second.x;
	tmp_2.y = tmp.y;
	brznh_algo(win, tmp, tmp_2, color);
	brznh_algo(win, tmp_2, second, color);
}

void	smaller_x(t_win *win, t_dot first, t_dot second, int color)
{
	// dprintf(my_fd, "SMALLER_X\n");
	change_value(win, &first, &second);
	if (first.y == second.y)
	{
		brznh_algo(win, first, second, color);
		// if (win->flag)
		// 	brznh_algo(win, first, second, color);
		return ;
	}
	if (first.y < second.y)
	{
		// dprintf(my_fd, "SMALLER_X SMALLER_Y\n");
		first_y_smaller_1(win, first, second, color);
		// if (win->flag)
		// 	first_y_smaller_1(win, first, second, color);
	}
	else
	{
		// dprintf(my_fd, "SMALLER_X BIGGER_Y\n");
		first_y_bigger_1(win, first, second, color);
		// if (win->flag)
		// 	first_y_bigger_1(win, first, second, color);
	}
}
