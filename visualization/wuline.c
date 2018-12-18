#include "view.h"

int		IPart(float x)
{
	return (int)x;
}

float	FPart(float x)
{
	while (x >= 0)
		x--;
	x++;
	return (x);
}

void	draw_loop(t_win *win, int start, int end, float inter, float grad)
{
	int		i;
	int		tmp_i;
	int		tmp_f;
	
	i = start + 1;
	while (i < end)
	{
		tmp_i = IPart(inter);
		tmp_f = (int)(COLOR - FPart(inter) * COLOR);
		mlx_pixel_put(win->mlx_ptr, win->win_ptr, tmp_i, i, tmp_f);
		tmp_f = (int)(FPart(inter) * COLOR);
		mlx_pixel_put(win->mlx_ptr, win->win_ptr, tmp_i + 1, i, tmp_f);
		inter += grad;
		i++;
	}
}

void	x_line(t_win *win, t_dot start, t_dot end, float grad)
{
	float	intery;
	int		tmp_i;
	int		tmp_f;
	int		i;

	if (end.x < start.x)
	{
		end.x += start.x;
		start.x = end.x - start.x;
		end.x -= start.x;
		end.y += start.y;
		start.y = end.y - start.y;
		end.y -= start.y;
	}
	if (end.y < start.y)
		grad = -grad;
	intery = start.y + grad;
	mlx_pixel_put(win->mlx_ptr, win->win_ptr, start.x, start.y, COLOR);
	// draw_loop(win, start.x, end.x, intery, grad);
	i = start.x + 1;
	while (i < end.x)
	{
		tmp_i = IPart(intery);
		tmp_f = (int)(COLOR -  FPart(intery) * COLOR);
		mlx_pixel_put(win->mlx_ptr, win->win_ptr, i, tmp_i, tmp_f);
		tmp_f = (int)(FPart(intery) * COLOR);
		mlx_pixel_put(win->mlx_ptr, win->win_ptr, i, tmp_i + 1, tmp_f);
		intery += grad;
		i++;
	}
	mlx_pixel_put(win->mlx_ptr, win->win_ptr, end.x, end.y, COLOR);
}

void	y_line(t_win *win, t_dot start, t_dot end, float grad)
{
	float	interx;
	int		tmp_i;
	int		tmp_f;
	int		i;

	if (end.y < start.y)
	{
		end.x += start.x;
		start.x = end.x - start.x;
		end.x -= start.x;
		end.y += start.y;
		start.y = end.y - start.y;
		end.y -= start.y;
	}
	if (end.x < start.x)
		grad = -grad;
	interx = start.x + grad;
	mlx_pixel_put(win->mlx_ptr, win->win_ptr, start.x, start.y, COLOR);
	// draw_loop(win, start.y, end.y, interx, grad);
	i = start.y + 1;
	while (i < end.y)
	{
		tmp_i = IPart(interx);
		tmp_f = (int)(COLOR - FPart(interx) * COLOR);
		mlx_pixel_put(win->mlx_ptr, win->win_ptr, tmp_i, i, tmp_f);
		tmp_f = (int)(FPart(interx) * COLOR);
		mlx_pixel_put(win->mlx_ptr, win->win_ptr, tmp_i + 1, i, tmp_f);
		interx += grad;
		i++;
	}
	mlx_pixel_put(win->mlx_ptr, win->win_ptr, end.x, end.y, COLOR);
}

void	drawWuLine(t_win *win, t_dot start, t_dot end)
{
	int		dx;
	int		dy;
	float	grad;

	dx = (end.x > start.x) ? (end.x - start.x) : (start.x - end.x);
	dy = (end.y > start.y) ? (end.y - start.y) : (start.y - end.y);
	//Если линия параллельна одной из осей, рисуем обычную линию - заполняем все пикселы в ряд
	if (dx == 0 || dy == 0)
	{
		brznh_algo(win, start, end);
		return;
	}
	//Для Х-линии (коэффициент наклона < 1)
	if (dy < dx)
	{
		grad = (float)dy / dx;
		x_line(win, start, end, grad);
	}
	//Для Y-линии (коэффициент наклона > 1)
	else
	{
		grad = (float)dx / dy;
		y_line(win, start, end, grad);
	}
}
//Метод, устанавливающий пиксел на форме с заданными цветом и прозрачностью
// void	PutPixel(Graphics g, Color col, int x, int y, int alpha)
// {
// 	g.FillRectangle(new SolidBrush(Color.FromArgb(alpha, col)), x, y, 1, 1);
// }