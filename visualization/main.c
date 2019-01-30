/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 13:59:32 by omaslova          #+#    #+#             */
/*   Updated: 2018/11/24 13:59:33 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "view.h"

// void		drawSquareLineLeft(t_win *win, t_dot first, t_dot second)
// {
// 	t_dot	*tmp;
// 	t_dot	*tmp_2;

	
// 	tmp = (t_dot *)ft_memalloc(sizeof(t_dot));
// 	tmp_2 = (t_dot *)ft_memalloc(sizeof(t_dot));
// 	dprintf(my_fd, "1 Y = %d, 2 Y = %d\n", first.y, second.y);
// 	if (first.x < second.x)
// 	{
// 		brznh_algo(win, second, first);
// 		// dprintf(my_fd, "\nFIRST CASE");
// 		// tmp->x = first.x;
// 		// tmp->y = second.y;
// 		// dprintf(my_fd, "\ntmp: (%d, %d)\n", tmp->x, tmp->y);
// 		// brznh_algo(win, *tmp, first);
// 		// // drawWuLine(win, *tmp, first);
// 		// tmp_2->x = second.x;
// 		// tmp_2->y = tmp->y;
// 		// dprintf(my_fd, "tmp_2: (%d, %d)\n", tmp_2->x, tmp_2->y);
// 		// brznh_algo(win, *tmp, *tmp_2);

// 		// tmp->y = second.y;
// 		// tmp->x = second.x;
// 		// dprintf(my_fd, "tmp_3: (%d, %d)\n\n", tmp->x, tmp->y);
// 		// brznh_algo(win, *tmp_2, *tmp);
// 	}
// 	else if (first.x == second.x)
// 		brznh_algo(win, first, second);
// 	else
// 	{
// 		// dprintf(my_fd, "\nSECOND CASE");
// 		// tmp->x = second.x + (CELL_SIZE * 2);
// 		// tmp->y = first.y;
// 		// dprintf(my_fd, "\ntmp: (%d, %d)\n", tmp->x, tmp->y);
// 		// brznh_algo(win, *tmp, first);
// 		// // drawWuLine(win, *tmp, first);
// 		// tmp_2->x = tmp->x;
// 		// tmp_2->y = second.y;
// 		// dprintf(my_fd, "tmp_2: (%d, %d)\n", tmp_2->x, tmp_2->y);
// 		// brznh_algo(win, *tmp, *tmp_2);
		
// 		brznh_algo(win, first, second);

// 		// tmp->y = second.y;
// 		// tmp->x = second.x;
// 		// dprintf(my_fd, "tmp_3: (%d, %d)\n\n", tmp->x, tmp->y);
// 		// brznh_algo(win, *tmp_2, *tmp);
// 	}
// }

// void		drawSquareLineRight(t_win *win, t_dot first, t_dot second)
// {
// 	t_dot	*tmp;
// 	t_dot	*tmp_2;

	
// 	tmp = (t_dot *)ft_memalloc(sizeof(t_dot));
// 	tmp_2 = (t_dot *)ft_memalloc(sizeof(t_dot));
// 	dprintf(my_fd, "1 Y = %d, 2 Y = %d\n", first.y, second.y);
// 	if (first.x == second.x)
// 		brznh_algo(win, first, second);
// 	else if (first.x < second.x)
// 	{
// 		// brznh_algo(win, second, first);
// 		dprintf(my_fd, "\nFIRST CASE");
// 		tmp->x = first.x + win->right->x;
// 		tmp->y = first.y;
// 		dprintf(my_fd, "\ntmp: (%d, %d)\n", tmp->x, tmp->y);
// 		brznh_algo(win, *tmp, first);
// 		// drawWuLine(win, *tmp, first);
// 		tmp_2->x = tmp->x;
// 		tmp_2->y = second.y;
// 		dprintf(my_fd, "tmp_2: (%d, %d)\n", tmp_2->x, tmp_2->y);
// 		brznh_algo(win, *tmp, *tmp_2);
// 		tmp->y = second.y;
// 		tmp->x = second.x;
// 		dprintf(my_fd, "tmp_3: (%d, %d)\n\n", tmp->x, tmp->y);
// 		brznh_algo(win, *tmp_2, *tmp);
// 	}
// 	else
// 	{
// 		// brznh_algo(win, second, first);
// 		dprintf(my_fd, "\nSECOND CASE");
// 		tmp->y = first.y;
// 		tmp->x = win->right->x + (CELL_SIZE * 2);
// 		dprintf(my_fd, "\ntmp: (%d, %d)\n", tmp->x, tmp->y);
// 		brznh_algo(win, first, *tmp);
// 		// drawWuLine(win, *tmp, first);
// 		tmp_2->x = tmp->x;
// 		tmp_2->y = second.y - (CELL_SIZE * 2);
// 		dprintf(my_fd, "tmp_2: (%d, %d)\n", tmp_2->x, tmp_2->y);
// 		brznh_algo(win, *tmp, *tmp_2);
// 		tmp->x = second.x;
// 		tmp->y = second.y - (CELL_SIZE * 2);
// 		dprintf(my_fd, "tmp_3: (%d, %d)\n", tmp->x, tmp->y);
// 		brznh_algo(win, *tmp, *tmp_2);
// 		brznh_algo(win, *tmp, second);
// 	}
// }

int			exit_x(void *par)
{
	par = NULL;
	exit(1);
	return (0);
}

// t_ant		*search_ant(t_ant *ants, int num)
// {
// 	if (ants[num - 1].num != 0)
// 		return (&ants[num - 1]);
// 	return (NULL);
// }

void		define_ant(t_win *win, char *line, int *color, int i)
{
	int		pos;
	int		num;
	char	*ptr;

	ptr = ft_strchr(line, '-');
	// dprintf(my_fd, "line + 1 = %s\n", line + 1);
	num = ft_atoi(line + 1);
	ptr += 1;
	pos = search_by_name(win->graph->graph, ptr, 0);
	// dprintf(my_fd, "ptr = %s, num = %d, pos = %d\n", ptr, num, pos);
	// dprintf(my_fd, "win->ants[num - 1].num = %d\n", win->ants[num - 1].num);
	if (win->ants[num - 1].num == 0 && win->ants[num - 1].prev_room == 0)
	{
		win->ants[num - 1].num = num;
		// dprintf(my_fd, "win->ants[num - 1].num = %d\n", win->ants[num - 1].num);
		win->ants[num - 1].color = *color;
		win->ants[num - 1].prev_room = 0;
		*color += win->color_step;
	}
	// else
	// {
	// 	win->ants[num - 1].prev_room = pos;
	// }
	win->rooms[i][1] = pos;
}

void		clear_rooms(t_win *win, int lim)
{
	int i;

	i = 0;
	while (i < lim)
	{
		free(win->rooms[i]);
		i++;
	}
	free(win->rooms);
}

int			run(t_win *win)
{
	int		i;
	int		color;
	char	**arr;
	char	*line;

	win->ants = (t_ant *)ft_memalloc(sizeof(t_ant) * win->graph->ant_amount);
	color = 0x000000;
	dprintf(my_fd, "color_step = %d\n", win->color_step);
	while (get_next_line(0, &line) > 0)
	{
		dprintf(my_fd, "line = %s\n", line);
		if (ft_strchr(line, 'L'))
		{
			i = 0;
			win->rooms = (int **)ft_memalloc(sizeof(int *) * (ft_countchar(line, ' ') + 1));
			arr = ft_strsplit(line, ' ');
			while (arr[i] != NULL)
			{
				win->rooms[i] = (int *)ft_memalloc(sizeof(int) * 2);
				define_ant(win, arr[i], &color, i);
				win->rooms[i][0] = color;
				free(arr[i]);
				i++;
			}
			win->rooms[i] = (int *)ft_memalloc(sizeof(int) * 2);
			win->rooms[i][0] = -1;
			free(arr);
			mlx_clear_window(win->mlx_ptr, win->win_ptr);
			matrix_to_default(win);
			draw_anthill(win);
			clear_rooms(win, i + 1);
			usleep(DELAY);
			break ;
		}
		free(line);
	}
	return (0);
}

static int	key_hook(int keycode, t_win *win)
{
	if (keycode == 53)
	{
		free(win);
		mlx_destroy_window(win->mlx_ptr, win->win_ptr);
		exit(0);
	}
	else if (keycode == 69)
		CELL_SIZE += 1;
	else if (keycode == 78)
		CELL_SIZE -= 1;
	else if (keycode == 124)
		MOVE_SIDE += 10;
	else if (keycode == 123)
		MOVE_SIDE -= 10;
	else if (keycode == 125)
		MOVE_UP += 10;
	else if (keycode == 126)
		MOVE_UP -= 10;
	if (keycode == 49)
	{
		mlx_loop_hook(win->mlx_ptr, run, win);
	}
	else
	{
		mlx_clear_window(win->mlx_ptr, win->win_ptr);
		matrix_to_default(win);
		draw_anthill(win);
	}
	return (0);
}

int			main(void)
{
	t_win	*win;

	my_fd = open("logg", O_RDWR | O_CREAT | O_TRUNC);
	win = (t_win *)ft_memalloc(sizeof(t_win));
	win->graph = (t_graph *)ft_memalloc(sizeof(t_graph));
	win->mlx_ptr = mlx_init();
	win->win_ptr = mlx_new_window(win->mlx_ptr, WIDTH, HEIGTH, "Lem_in");
	init(&win);
	draw_anthill(win);
	mlx_hook(win->win_ptr, 2, 0, key_hook, win);
	mlx_hook(win->win_ptr, 17, 1L << 17, exit_x, 0);
	mlx_loop(win->mlx_ptr);
	return (0);
}
