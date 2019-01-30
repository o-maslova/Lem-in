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

void		smaller_x(t_win *win, t_dot first, t_dot second, int color)
{
	t_dot *tmp;
	t_dot *tmp_2;

	// dprintf(my_fd, "SMALLER_X\n");
	change_value(win, &first, &second);
	if (first.y == second.y)
	{
		brznh_algo(win, first, second, color);
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
		// dprintf(my_fd, "SMALLER_X SMALLER_Y\n");
		// tmp->x = first.x;
		tmp->y = second.y + CELL_SIZE;
		// brznh_algo(win, first, second, color);
		// brznh_algo(win, *tmp, first);
		// tmp_2->x = second.x;
		// tmp_2->y = tmp->y;
		// brznh_algo(win, *tmp, *tmp_2);
		// brznh_algo(win, *tmp_2, second);
	}
	else
	{
		// dprintf(my_fd, "SMALLER_X BIGGER_Y\n");
		// tmp->x = first.x;
		tmp->y = first.y + CELL_SIZE;
	}
	brznh_algo(win, *tmp, first, color);
	// brznh_algo(win, *tmp, second, color);
	brznh_algo(win, *tmp, first, color);
	tmp_2->x = second.x;
	tmp_2->y = tmp->y;
	brznh_algo(win, *tmp, *tmp_2, color);
	brznh_algo(win, *tmp_2, second, color);
	free(tmp);
}

void		bigger_x(t_win *win, t_dot first, t_dot second, int color)
{
	t_dot *tmp;
	t_dot *tmp_2;


	// dprintf(my_fd, "BIGGER_X\n");
	change_value(win, &first, &second);
	if (first.y == second.y)
	{
		brznh_algo(win, first, second, color);
		return ;
	}
	tmp = (t_dot *)ft_memalloc(sizeof(t_dot));
	tmp_2 = (t_dot *)ft_memalloc(sizeof(t_dot));
	// find_min(win, first);
	if (first.y < second.y)
	{
		// dprintf(my_fd, "BIGGER_X SMALLER_Y\n");
		tmp->x = first.x;
		tmp->y = second.y;
		brznh_algo(win, *tmp, first, color);
		brznh_algo(win, *tmp, second, color);
		// brznh_algo(win, first, second);
	}
	else
	{
		first.x += (CELL_SIZE - 1) / 2;
		first.y += (CELL_SIZE - 1) / 2;
		// dprintf(my_fd, "BIGGER_X BIGGER_Y\n");
		tmp->x = first.x + CELL_SIZE;
		tmp->y = first.y;
		brznh_algo(win, *tmp, first, color);
		tmp_2->x = tmp->x;
		tmp_2->y = second.y - CELL_SIZE;
		brznh_algo(win, *tmp, *tmp_2, color);
		tmp->x = second.x;
		tmp->y = tmp_2->y;
		brznh_algo(win, *tmp_2, *tmp, color);
		brznh_algo(win, *tmp, second, color);
	}
	free(tmp);
}

void		draw_links(t_win *win)
{
	int		i;
	int		j;
	int		k;
	int		color;
	t_dot	first;
	t_dot	second;

	i = 0;
	k = 0;
	while (i < win->graph->rooms)
	{
		j = 0;
		while (j < win->graph->rooms)
		{
			if (win->graph->links[i][j] == 1)
			{
				if (win->rooms)
				{
					win->flag = 1;
					if (win->rooms[k][1] == j)
						color = win->rooms[k++][0];
					else
						color = COLOR;
				}
				else
					color = COLOR;
				dprintf(my_fd, "\ncolor = %d\n", color);
				first = search_by_pos(win->graph->graph, i);
				second = search_by_pos(win->graph->graph, j);
				win->graph->links[i][j] = -1;
				win->graph->links[j][i] = -1;
				// find_min(win, first);
				// dprintf(my_fd, "first_x = %d, first_y = %d\n", first.x, first.y);
				// dprintf(my_fd, "second_x = %d, second_y = %d\n", second.x, second.y);
				if (first.x > second.x)
					bigger_x(win, first, second, color);
				else if (first.x == second.x)
				{
					change_value(win, &first, &second);
					brznh_algo(win, first, second, color);
				}
				else
					smaller_x(win, first, second, color);
			}
			j++;
		}
		i++;
	}
	// dprintf(my_fd, "\nmin_up = %d\n", win->min_up);
	// dprintf(my_fd, "min_down = %d\n", win->min_down);
	// dprintf(my_fd, "min_left = %d\n", win->min_left);
	// dprintf(my_fd, "min_right = %d\n\n", win->min_right);
}

void		draw_room(t_win *win, int x, int y, int color)
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
			mlx_pixel_put(win->mlx_ptr, win->win_ptr, i, j, color);
			j++;
		}
		i++;
	}
	dprintf(my_fd, "\n");
}

int		search_in_rooms(t_win *win, int pos)
{
	int i;

	i = 0;
	while (win->rooms[i][0] != -1)
	{
		dprintf(my_fd, "win->rooms[i][1] = %d\n", win->rooms[i][1]);
		if (win->rooms[i][1] == pos)
			return (i);
		i++;
	}
	return (-1);
}

void		draw_anthill(t_win *win)
{
	int		x;
	int		y;
	int		i;
	int		color;
	t_vert	*tmp;

	x = 0;
	y = 0;
	i = -1;
	tmp = win->graph->graph;
	while (tmp)
	{
		if (win->rooms)
		{
			i = search_in_rooms(win, tmp->pos);
			dprintf(my_fd, "i_search = %d\n", i);
			color = i >= 0 ? win->rooms[i][0] : COLOR;
		}
		if (i < 0)
		{
			if (tmp->is_start)
				color = 0xf4e542;
			else if (tmp->is_end)
				color = 0x0000FF;
			else
				color = COLOR;
		}
		dprintf(my_fd, "ROOM name %d\n", tmp->pos);
		dprintf(my_fd, "color = %d\n", color);
		x = (tmp->x * CELL_SIZE) + MOVE_SIDE;
		y = (tmp->y * CELL_SIZE) + MOVE_UP;
		draw_room(win, x, y, color);
		// mlx_pixel_put(win->mlx_ptr, win->win_ptr, tmp->x, tmp->y, COLOR);
		tmp = tmp->next;
	}
	draw_links(win);
}
