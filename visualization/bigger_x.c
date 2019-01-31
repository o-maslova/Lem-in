#include "view.h"

void	first_y_bigger_2(t_win *win, t_dot first, t_dot second, int color)
{
	t_dot tmp;
	t_dot tmp_2;

	// dprintf(my_fd, "BIGGER_X BIGGER_Y\n");
	first.x += (CELL_SIZE - 1) / 2;
	first.y += (CELL_SIZE - 1) / 2;
	tmp.x = first.x + CELL_SIZE;
	tmp.y = first.y;
	brznh_algo(win, tmp, first, color);
	tmp_2.x = tmp.x;
	tmp_2.y = second.y - CELL_SIZE;
	brznh_algo(win, tmp, tmp_2, color);
	tmp.x = second.x;
	tmp.y = tmp_2.y;
	brznh_algo(win, tmp_2, tmp, color);
	brznh_algo(win, tmp, second, color);
}

void	first_y_smaller_2(t_win *win, t_dot first, t_dot second, int color)
{
	t_dot tmp;

	tmp.x = first.x;
	tmp.y = second.y;
	brznh_algo(win, tmp, first, color);
	brznh_algo(win, tmp, second, color);
}

void		bigger_x(t_win *win, t_dot first, t_dot second, int color)
{
	// dprintf(my_fd, "BIGGER_X\n");
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