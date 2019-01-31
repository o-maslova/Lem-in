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

void		draw_links(t_win *win)
{
	int		i;
	int		j;
	t_dot	first;
	t_dot	second;

	i = 0;
	while (i < win->graph->rooms)
	{
		j = 0;
		while (j < win->graph->rooms)
		{
			if (win->graph->links[i][j] == 1)
			{
				first = search_by_pos(win->rooms, i);
				second = search_by_pos(win->rooms, j);
				win->graph->links[i][j] = -1;
				win->graph->links[j][i] = -1;
				// find_min(win, first);
				// dprintf(my_fd, "first_x = %d, first_y = %d\n", first.x, first.y);
				// dprintf(my_fd, "second_x = %d, second_y = %d\n", second.x, second.y);
				if (first.x > second.x)
					bigger_x(win, first, second, COLOR);
				else if (first.x == second.x)
				{
					change_value(win, &first, &second);
					brznh_algo(win, first, second, COLOR);
				}
				else
					smaller_x(win, first, second, COLOR);
			}
			j++;
		}
		i++;
	}
}

void		draw_room(t_win *win, int x, int y, int color)
{
	int		i;
	int		j;

	i = x;
	// dprintf(my_fd, "x = %d, y = %d\n", x, y);
	// BresenhamCircle(win, x, y, CELL_SIZE);
	while (i < x + CELL_SIZE)
	{
		j = y;
		while (j < y + CELL_SIZE)
		{
			pixel_put_img(win, i, j, color);
			j++;
		}
		i++;
	}
	// dprintf(my_fd, "\n");
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
	draw_links(win);
	while (tmp)
	{
		if (i < 0)
		{
			if (tmp->is_start)
				color = 0xf4e542;
			else if (tmp->is_end)
				color = 0x008080;
			else
				color = COLOR;
		}
		x = (tmp->x * CELL_SIZE) + MOVE_SIDE;
		y = (tmp->y * CELL_SIZE) + MOVE_UP;
		draw_room(win, x, y, color);
		tmp = tmp->next;
	}
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
}

void		go(t_win *win)
{
	int i;
	t_dot	first;
	t_dot	second;

	i = 0;
	while (win->ants[i].num != 0)
	{
		first = search_by_pos(win->rooms, win->ants[i].prev_room);
		second = search_by_pos(win->rooms, win->ants[i].next_room);
		if (first .x > second.x)
			bigger_x(win, first, second, win->ants[i].color);
		else if (first.x == second.x)
		{
			change_value(win, &first, &second);
			brznh_algo(win, first, second, win->ants[i].color);
		}
		else
			smaller_x(win, first, second, win->ants[i].color);
		i++;
	}
}

void	make_threads(t_win *win)
{
	int			i;
	int			j;
	t_win		tab[win->graph->ant_amount];
	pthread_t	threads[win->graph->ant_amount];

	i = 0;
	j = 0;
	while (i < win->graph->ant_amount)
	{
		ft_memcpy((void *)&tab[i], (void *)win, sizeof(t_win));
		tab[i].cel_start = j;
		j += HEIGTH / win->graph->ant_amount;
		tab[i].cel_end = j;
		pthread_create(&threads[i], NULL, (void *)go, &tab[i]);
		i++;
	}
	while (i-- > 0)
		pthread_join(threads[i], NULL);
	// mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
	// mlx_put_image_to_window(frl->mlx_ptr, frl->win_ptr, frl->img_ptr, 0, 0);
}

