#include "view.h"

void		smaller_x(t_win *win, t_dot first, t_dot second)
{
	t_dot *tmp;

	tmp = (t_dot *)ft_memalloc(sizeof(t_dot));
	if (first.y < second.y)
	{
		tmp->x = second.x;
		tmp->y = first.y;
		brznh_algo(win, *tmp, first);
		brznh_algo(win, *tmp, second);
	}
	else if (first.y == second.y)
		brznh_algo(win, first, second);
	else
	{
		tmp->x = first.x;
		tmp->y = second.y;
		brznh_algo(win, *tmp, first);
		brznh_algo(win, *tmp, second);
	}
	free(tmp);
}

void		bigger_x(t_win *win, t_dot first, t_dot second)
{
	t_dot *tmp;

	tmp = (t_dot *)ft_memalloc(sizeof(t_dot));
	if (first.y < second.y)
	{
		tmp->x = first.x;
		tmp->y = second.y;
		brznh_algo(win, *tmp, first);
		brznh_algo(win, *tmp, second);
	}
	else if (first.y == second.y)
		brznh_algo(win, first, second);
	else
	{
		tmp->x = second.x;
		tmp->y = first.y;
		brznh_algo(win, *tmp, first);
		brznh_algo(win, *tmp, second);
	}
	free(tmp);
}

void		draw_links(t_win *win, t_vert *graph, int **links)
{
	int		i;
	int		j;
	t_dot	first;
	t_dot	second;

	i = 0;
	while (i < g_amount)
	{
		j = 0;
		while (j < g_amount)
		{
			if (links[i][j] == 1)
			{
				dprintf(my_fd, "\ni = %d, j = %d\n", i, j);
				first = search_by_pos(graph, i);
				second = search_by_pos(graph, j);
				links[i][j] = -1;
				links[j][i] = -1;
				first.x = (first.x * CELL_SIZE) + (CELL_SIZE / 2);
				second.x = (second.x * CELL_SIZE) + (CELL_SIZE / 2);
				first.y = (first.y * CELL_SIZE) + (CELL_SIZE / 2);
				second.y = (second.y * CELL_SIZE) + (CELL_SIZE / 2);
				first.x += MOVE_SIDE;
				second.x += MOVE_SIDE;
				first.y += MOVE_UP;
				second.y += MOVE_UP;
				dprintf(my_fd, "first_x = %d, first_y = %d\n", first.x, first.y);
				dprintf(my_fd, "second_x = %d, second_y = %d\n", second.x, second.y);
				if (first.x > second.x)
					bigger_x(win, first, second);
				// else if (first.x == second.x)
				// 	brznh_algo(win, first, second);
				else
					smaller_x(win, first, second);
			}
			j++;
		}
		i++;
	}
}

void		draw_room(t_win *win, int x, int y)
{
	int		i;
	int		j;

	i = x;
	dprintf(my_fd, "x = %d, y = %d\n", x, y);
	// BresenhamCircle(win, x, y, CELL_SIZE);
	while (i < x + CELL_SIZE)
	{
		j = y;
		while (j < y + CELL_SIZE)
		{
			mlx_pixel_put(win->mlx_ptr, win->win_ptr, i, j, COLOR);
			j++;
		}
		i++;
	}
	dprintf(my_fd, "\n");
}

void		draw_anthill(t_win *win, t_vert *graph, int **links)
{
	int		x;
	int		y;
	int		max[2];
	t_vert	*tmp;

	x = 0;
	y = 0;
	tmp = graph;
	max[0] = tmp->x;
	while (tmp)
	{
		// dprintf(my_fd, "x = %d, y = %d\n", tmp->x, tmp->y);
		x = (tmp->x * CELL_SIZE) + MOVE_SIDE;
		y = (tmp->y * CELL_SIZE) + MOVE_UP;
		if (x > max[0])
		{
			max[0] = x;
			max[1] = y;
		}
		draw_room(win, x, y);
		// pixel_put_img(win, tmp->x, tmp->y, COLOR);
		tmp = tmp->next;
	}
	// links = NULL;
	draw_links(win, graph, links);
}
