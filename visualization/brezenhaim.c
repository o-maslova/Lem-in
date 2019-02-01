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

void	draw_vert_line(t_win *win, int dot_x, int dot_y, int color)
{
	int x;
	int y;
	int i;
	int mul;

	x = dot_x;
	y = dot_y;
	// color = color != COLOR ? 0xFF0000 : COLOR;
	mul = color != COLOR ? 100 : 0;
	dprintf(my_fd, "mul = %d\n", mul);
	win->var->err = win->var->len_y * -1;
	win->var->length += 1;
	// win->var->length += 1;
	while (win->var->length--)
	{
		i = 0;
		// usleep(mul);
		pixel_put_img(win, x, y, color);
		// if (mul)
		// 	mlx_pixel_put(win->mlx_ptr, win->win_ptr, x, y, 0x000000);
		y += win->var->d_y;
		win->var->err += 2 * win->var->len_x;
		if (win->var->err > 0)
		{
			win->var->err -= 2 * win->var->len_y;
			x += win->var->d_x;
		}
		// if (mul)
		// {
		// 	pixel_put_img(win, x, y, 0xFF0000);
		// 	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
		// 	// usleep(mul);
		// }
	}
}

void	draw_horiz_line(t_win *win, int dot_x, int dot_y, int color)
{
	int x;
	int y;
	int i;
	int mul;

	x = dot_x;
	y = dot_y;
	// color = color != COLOR ? 0xFF0000 : COLOR;
	mul = color != COLOR ? 100 : 0;
	dprintf(my_fd, "mul = %d\n", mul);
	win->var->err = win->var->len_x * -1;
	win->var->length += 1;
	while (win->var->length--)
	{
		i = 0;
		// mlx_pixel_put(win->mlx_ptr, win->win_ptr, 701, 701, COLOR);
		pixel_put_img(win, x, y, color);
		// if (mul)
		// 	mlx_pixel_put(win->mlx_ptr, win->win_ptr, x, y, 0x000000);
		x += win->var->d_x;
		win->var->err += 2 * win->var->len_y;
		if (win->var->err > 0)
		{
			win->var->err -= 2 * win->var->len_x;
			y += win->var->d_y;
		}
		// if (mul)
		// {
		// 	pixel_put_img(win, x, y, 0xFF0000);
		// 	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
		// 	// usleep(mul);
		// }
	}
}

void	brznh_algo(t_win *win, int *start, int *end, int color)
{
	int		x;
	int		y;
	// int		mul;

	x = start[0];
	y = start[1];
	win->var->len_x = abs(end[0] - x);
	win->var->len_y = abs(end[1] - y);
	win->var->length = MAX(win->var->len_x, win->var->len_y);
	win->var->d_x = POS(end[0] - start[0]);
	win->var->d_y = POS(end[1] - start[1]);
	// mul = color != COLOR ? 100 : 0;
	if (win->var->length == 0)
	{
		pixel_put_img(win, x, y, color);
		// if (mul)
		// {
		// 	dprintf(my_fd, "here\n");
		// 	pixel_put_img(win, x + 1, y + 1, 0xFF0000);
		// 	// usleep(mul);
		// 	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
		// }
	}
	if (win->var->len_y <= win->var->len_x)
		draw_horiz_line(win, start[0], start[1], color);
	else
		draw_vert_line(win, start[0], start[1], color);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
}