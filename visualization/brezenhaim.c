#include "view.h"

void	BresenhamCircle(t_win *win, int x0, int y0, int radius)
{
	int x = radius;
	int y = 0;
	int radiusError = 1 - x;
	
	while (x >= y)
	{
		mlx_pixel_put(win->mlx_ptr, win->win_ptr, x + x0, y + y0, COLOR);
		mlx_pixel_put(win->mlx_ptr, win->win_ptr, y + x0, x + y0, COLOR);
		mlx_pixel_put(win->mlx_ptr, win->win_ptr, -x + x0, y + y0, COLOR);
		mlx_pixel_put(win->mlx_ptr, win->win_ptr, -y + x0, x + y0, COLOR);
		mlx_pixel_put(win->mlx_ptr, win->win_ptr, -x + x0, -y + y0, COLOR);
		mlx_pixel_put(win->mlx_ptr, win->win_ptr, -y + x0, -x + y0, COLOR);
		mlx_pixel_put(win->mlx_ptr, win->win_ptr, x + x0, -y + y0, COLOR);
		mlx_pixel_put(win->mlx_ptr, win->win_ptr, y + x0, -x + y0, COLOR);
		y++;
		if (radiusError < 0)
		{
			radiusError += 2 * y + 1;
		}
		else
		{
			x--;
			radiusError += 2 * (y - x + 1);
		}
	}
}

int		lalala(t_fu *test)
{
	mlx_pixel_put(test->mlx_ptr, test->win_ptr, test->x, test->y, test->color);
	return (1);
}

void	draw_vert_line(t_win *win, int dot_x, int dot_y, int color)
{
	int x;
	int y;
	int mul;
	t_fu test;

	x = dot_x;
	y = dot_y;
	test.color = color;
	test.mlx_ptr = win->mlx_ptr;
	test.win_ptr = win->win_ptr;
	mul = win->flag == 1 ? 10 : 0;
	win->var->err = win->var->len_y * -1;
	win->var->length += 1;
	while (win->var->length--)
	{
		test.x = x;
		test.y = y;
		// usleep(mul);
		mlx_pixel_put(win->mlx_ptr, win->win_ptr, x, y, color);
		y += win->var->d_y;
		win->var->err += 2 * win->var->len_x;
		if (win->var->err > 0)
		{
			win->var->err -= 2 * win->var->len_y;
			x += win->var->d_x;
		}
		if (win->flag)
			mlx_loop_hook(win->mlx_ptr, lalala, &test);
	}
}

void	draw_horiz_line(t_win *win, int dot_x, int dot_y, int color)
{
	int x;
	int y;
	int mul;
	t_fu test;

	x = dot_x;
	y = dot_y;
	mul = win->flag == 1 ? 10 : 0;
	win->var->err = win->var->len_x * -1;
	win->var->length += 1;
	test.color = color;
	test.mlx_ptr = win->mlx_ptr;
	test.win_ptr = win->win_ptr;
	while (win->var->length--)
	{
		test.x = x;
		test.y = y;
		// usleep(mul);
		mlx_pixel_put(win->mlx_ptr, win->win_ptr, x, y, color);
		x += win->var->d_x;
		win->var->err += 2 * win->var->len_y;
		if (win->var->err > 0)
		{
			win->var->err -= 2 * win->var->len_x;
			y += win->var->d_y;
		}
		if (win->flag)
			mlx_loop_hook(win->mlx_ptr, lalala, &test);
	}
}

void	brznh_algo(t_win *win, t_dot start, t_dot end, int color)
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
		mlx_pixel_put(win->mlx_ptr, win->win_ptr, x, y, color);
	if (win->var->len_y <= win->var->len_x)
		draw_horiz_line(win, start.x, start.y, color);
	else
		draw_vert_line(win, start.x, start.y, color);
}