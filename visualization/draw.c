#include "view.h"

void		xyz_to_xy(t_win *win, int x, int y, int *mod_room)
{
	double t_x;
	double t_y;
	double t_z;
	double z;

	t_x = (x * CELL_SIZE) + MOVE_SIDE;
	t_y = (y * CELL_SIZE) + MOVE_UP;
	t_z = 10;
	mod_room[1] = (int)(t_y * cos(R_X) + (t_z * -sin(R_X)));
	z = (int)(t_y * sin(R_X) + (t_z * cos(R_X)));
	t_z = (int)z;
	mod_room[0] = (int)(t_x * cos(R_Y) + (t_z * sin(R_Y)));
	mod_room[1] = (int)(t_x * -sin(R_Y) + (t_z * cos(R_Y)));
	t_y = (int)mod_room[1];
	t_x = (int)mod_room[0];
	mod_room[0] = (int)(t_x * cos(R_Z) + (t_y * -sin(R_Z)));
	mod_room[1] = (int)(t_y * cos(R_Z) + (t_x * sin(R_Z)));
	z = 0;
	// dprintf(my_fd, "AFTER MOD\nx = %d, y = %d\n", mod_room[0], mod_room[1]);
}

void		change_value(t_win *win, int *room, int i)
{
	room[0] = (room[0] * CELL_SIZE) + (CELL_SIZE / 2);
	// second[0] = (second[0] * CELL_SIZE) + (CELL_SIZE / 2);
	room[1] = (room[1] * CELL_SIZE) + (CELL_SIZE / 2);
	// second[1] = (second[1] * CELL_SIZE) + (CELL_SIZE / 2);
	room[0] += MOVE_SIDE;
	// second[0] += MOVE_SIDE;
	room[1] += MOVE_UP;
	// second[1] += MOVE_UP;
	xyz_to_xy(win, room[0], room[1], win->mod_rooms[i]);
}


void		draw_links(t_win *win)
{
	int		i;
	int		j;
	int		*first;
	int		*second;

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
				// dprintf(my_fd, "BEFORE MOD\nx1 = %d, y1 = %d\n", win->mod_rooms[i][0], win->mod_rooms[i][1]);
				// dprintf(my_fd, "x2 = %d, y2 = %d\n\n", win->mod_rooms[j][0], win->mod_rooms[j][1]);
				xyz_to_xy(win, first[0], first[1], win->mod_rooms[i]);
				xyz_to_xy(win, second[0], second[1], win->mod_rooms[j]);
				// brznh_algo(win, win->mod_rooms[i], win->mod_rooms[j], COLOR);
				// change_value(win, first, i);
				// change_value(win, second, j);
				// find_min(win, first);
				// dprintf(my_fd, "first_x = %d, first_y = %d\n", first.x, first.y);
				// dprintf(my_fd, "second_x = %d, second_y = %d\n", second.x, second.y);
				if (first[0] > second[0])
					bigger_x(win, win->mod_rooms[i], win->mod_rooms[j], COLOR);
				else if (first[0] == second[0])
				{
					// change_value(win, &first, &second);
					brznh_algo(win, win->mod_rooms[i], win->mod_rooms[j], COLOR);
				}
				else
					smaller_x(win, win->mod_rooms[i], win->mod_rooms[j], COLOR);
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

	x = x - (CELL_SIZE / 2);
	y = y - (CELL_SIZE / 2);
	i = x;
	dprintf(my_fd, "x = %d, y = %d\n", x, y);
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
	dprintf(my_fd, "\n");
}

void		draw_anthill(t_win *win)
{
	int		x;
	int		y;
	int		i;
	int		color;

	x = 0;
	y = 0;
	i = 0;
	draw_links(win);
	while (i < win->graph->rooms)
	{
		if (i == 0)
			color = 0xf4e542;
		else if (i == win->graph->end_room)
			color = 0x008080;
		else
			color = COLOR;
		xyz_to_xy(win, win->rooms[i][0], win->rooms[i][1], win->mod_rooms[i]);
		draw_room(win, win->mod_rooms[i][0], win->mod_rooms[i][1], color);
		i++;
	}
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
}

void		go(t_win *win)
{
	int i;
	int *first;
	int *second;
	int *tmp;

	i = 0;
	while (win->ants[i].num != -1)
	{
		if (win->ants[i].num == 0)
		{
			i++;
			continue ;
		}
		dprintf(my_fd, "win->ants[i].num %d\n", win->ants[i].num);
		first = search_by_pos(win->mod_rooms, win->ants[i].prev_room);
		second = search_by_pos(win->mod_rooms, win->ants[i].next_room);
		// xyz_to_xy(win, first[0], first[1], win->mod_rooms[win->ants[i].prev_room]);
		// xyz_to_xy(win, second[0], second[1], win->mod_rooms[win->ants[i].next_room]);
		// brznh_algo(win, first, second, win->ants[i].color);
		if (first[0] > second[0])
			bigger_x(win, first, second, win->ants[i].color);
		else if (first[0] == second[0])
			brznh_algo(win, first, second, win->ants[i].color);
		else
			smaller_x(win, first, second, win->ants[i].color);
		tmp = search_by_pos(win->rooms, win->ants[i].next_room);
		xyz_to_xy(win, tmp[0], tmp[1], win->mod_rooms[win->ants[i].next_room]);
		// dprintf(my_fd, "second[0]= %d, second[1] = %d\n", second[0], second[1]);
		draw_room(win, win->mod_rooms[win->ants[i].next_room][0], win->mod_rooms[win->ants[i].next_room][1], win->ants[i].color);
		if (win->ants[i].next_room == win->graph->end_room)
			win->ants[i].num = 0;
		// usleep(100000);
		i++;
	}
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
}

// void	make_threads(t_win *win)
// {
// 	int			i;
// 	int			j;
// 	t_win		tab[win->graph->ant_amount];
// 	pthread_t	threads[win->graph->ant_amount];

// 	i = 0;
// 	j = 0;
// 	while (i < win->graph->ant_amount)
// 	{
// 		ft_memcpy((void *)&tab[i], (void *)win, sizeof(t_win));
// 		tab[i].cel_start = j;
// 		j += HEIGTH / win->graph->ant_amount;
// 		tab[i].cel_end = j;
// 		pthread_create(&threads[i], NULL, (void *)go, &tab[i]);
// 		i++;
// 	}
// 	while (i-- > 0)
// 		pthread_join(threads[i], NULL);
// 	// mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
// 	// mlx_put_image_to_window(frl->mlx_ptr, frl->win_ptr, frl->img_ptr, 0, 0);
// }

