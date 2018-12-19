#include "view.h"

void		change_value(t_win *win, t_dot *first, t_dot *second)
{
	first->x = (first->x * CELL_SIZE) + (CELL_SIZE / 2);
	second->x = (second->x * CELL_SIZE) + (CELL_SIZE / 2);
	first->y = (first->y * CELL_SIZE) + (CELL_SIZE / 2);
	second->y = (second->y * CELL_SIZE) + (CELL_SIZE / 2);
	first->x += MOVE_SIDE;
	second->x += MOVE_SIDE;
	first->y += MOVE_UP;
	second->y += MOVE_UP;
}

void		find_min(t_win *win, t_dot dot)
{
	if (win->min_down < dot.y)
	{
		win->min_down = dot.y;
		// win->min_down = (win->min_down * CELL_SIZE) + (CELL_SIZE / 2) + MOVE_UP;
	}
	if (win->min_up > dot.y)
	{
		win->min_up = dot.y;
		// win->min_up = (win->min_up * CELL_SIZE) + (CELL_SIZE / 2) + MOVE_UP;
	}
	if (win->min_left > dot.x)
	{
		win->min_left = dot.x;
		// win->min_left = (win->min_left * CELL_SIZE) + (CELL_SIZE / 2) + MOVE_SIDE;
	}
	if (win->min_right < dot.x)
	{
		win->min_right = dot.x;
		// win->min_right = (win->min_right * CELL_SIZE) + (CELL_SIZE / 2) + MOVE_SIDE;
	}
}

void		smaller_x(t_win *win, t_dot first, t_dot second)
{
	t_dot *tmp;
	t_dot *tmp_2;

	dprintf(my_fd, "SMALLER_X\n");
	change_value(win, &first, &second);
	if (first.y == second.y)
	{
		brznh_algo(win, first, second);
		// free(tmp);
		// free(tmp_2);
		return ;
	}
	tmp = (t_dot *)ft_memalloc(sizeof(t_dot));
	tmp_2 = (t_dot *)ft_memalloc(sizeof(t_dot));
	// find_min(win, first);
	tmp->x = first.x;
	if (first.y < second.y)
	{
		dprintf(my_fd, "SMALLER_X SMALLER_Y\n");
		// tmp->x = first.x;
		tmp->y = second.y + CELL_SIZE;
		// brznh_algo(win, first, second);
		// brznh_algo(win, *tmp, first);
		// tmp_2->x = second.x;
		// tmp_2->y = tmp->y;
		// brznh_algo(win, *tmp, *tmp_2);
		// brznh_algo(win, *tmp_2, second);
	}
	else
	{
		dprintf(my_fd, "SMALLER_X BIGGER_Y\n");
		// tmp->x = first.x;
		tmp->y = first.y + CELL_SIZE;
	}
	brznh_algo(win, *tmp, first);
	// brznh_algo(win, *tmp, second);
	brznh_algo(win, *tmp, first);
	tmp_2->x = second.x;
	tmp_2->y = tmp->y;
	brznh_algo(win, *tmp, *tmp_2);
	brznh_algo(win, *tmp_2, second);
	free(tmp);
}

void		bigger_x(t_win *win, t_dot first, t_dot second)
{
	t_dot *tmp;
	t_dot *tmp_2;


	dprintf(my_fd, "BIGGER_X\n");
	change_value(win, &first, &second);
	if (first.y == second.y)
	{
		brznh_algo(win, first, second);
		return ;
	}
	tmp = (t_dot *)ft_memalloc(sizeof(t_dot));
	tmp_2 = (t_dot *)ft_memalloc(sizeof(t_dot));
	// find_min(win, first);
	if (first.y < second.y)
	{
		dprintf(my_fd, "BIGGER_X SMALLER_Y\n");
		tmp->x = first.x;
		tmp->y = second.y;
		brznh_algo(win, *tmp, first);
		brznh_algo(win, *tmp, second);
		// brznh_algo(win, first, second);
	}
	else
	{
		first.x += (CELL_SIZE - 1) / 2;
		first.y += (CELL_SIZE - 1) / 2;
		dprintf(my_fd, "BIGGER_X BIGGER_Y\n");
		tmp->x = first.x + CELL_SIZE;
		tmp->y = first.y;
		brznh_algo(win, *tmp, first);
		tmp_2->x = tmp->x;
		tmp_2->y = second.y - CELL_SIZE;
		brznh_algo(win, *tmp, *tmp_2);
		tmp->x = second.x;
		tmp->y = tmp_2->y;
		brznh_algo(win, *tmp_2, *tmp);
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
				// find_min(win, first);
				dprintf(my_fd, "first_x = %d, first_y = %d\n", first.x, first.y);
				dprintf(my_fd, "second_x = %d, second_y = %d\n", second.x, second.y);
				if (first.x > second.x)
					bigger_x(win, first, second);
				else if (first.x == second.x)
				{
					change_value(win, &first, &second);
					brznh_algo(win, first, second);
				}
				else
					smaller_x(win, first, second);
			}
			j++;
		}
		i++;
	}
	dprintf(my_fd, "\nmin_up = %d\n", win->min_up);
	dprintf(my_fd, "min_down = %d\n", win->min_down);
	dprintf(my_fd, "min_left = %d\n", win->min_left);
	dprintf(my_fd, "min_right = %d\n\n", win->min_right);
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
		// mlx_pixel_put(win->mlx_ptr, win->win_ptr, tmp->x, tmp->y, COLOR);
		tmp = tmp->next;
	}
	// links = NULL;
	draw_links(win, graph, links);
}
