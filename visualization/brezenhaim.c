#include "view.h"

void	draw_vert_line(t_win *win, int dot_x, int dot_y)
{
	int	x;
	int	y;

	x = dot_x;
	y = dot_y;
	win->var->err = win->var->len_y * -1;
	win->var->length += 1;
	while (win->var->length--)
	{
		mlx_pixel_put(win->mlx_ptr, win->win_ptr, x, y, 0xFFFFFF);
		y += win->var->d_y;
		win->var->err += 2 * win->var->len_x;
		if (win->var->err > 0)
		{
			win->var->err -= 2 * win->var->len_y;
			x += win->var->d_x;
		}
	}
}

void	draw_horiz_line(t_win *win, int dot_x, int dot_y)
{
	int	x;
	int	y;

	x = dot_x;
	y = dot_y;
	win->var->err = win->var->len_x * -1;
	win->var->length += 1;
	while (win->var->length--)
	{
		mlx_pixel_put(win->mlx_ptr, win->win_ptr, x, y, 0xFFFFFF);
		x += win->var->d_x;
		win->var->err += 2 * win->var->len_y;
		if (win->var->err > 0)
		{
			win->var->err -= 2 * win->var->len_x;
			y += win->var->d_y;
		}
	}
}

void	brznh_algo(t_win *win, t_vert start, t_vert end)
{
	int		x;
	int		y;

	x = start.x;
	y = start.y;
	win->var->len_x = abs(end.x - x);
	win->var->len_y = abs(end.y - y);
	win->var->length = MAX(win->var->len_x, win->var->len_y);
	win->var->d_x = POS(end.x - start.x);
	win->var->d_y = POS(end.y - start.y);
	if (win->var->length == 0)
		mlx_pixel_put(win->mlx_ptr, win->win_ptr, x, y, 0xFFFFFF);
	if (win->var->len_y <= win->var->len_x)
		draw_horiz_line(win, start.x, start.y);
	else
		draw_vert_line(win, start.x, start.y);
}