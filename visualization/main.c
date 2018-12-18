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
	mlx_clear_window(win->mlx_ptr, win->win_ptr);
	matrix_to_default(win->links);
	draw_anthill(win, win->graph, win->links);
	// else if (keycode == 49)
	// {
	// 	mlx_loop_hook(win->mlx_ptr, game, win);
	// }
	return (0);
}

int			main(int argc, char **argv)
{
	int		fd;
	char	*line;
	t_win	*win;

	my_fd = open("logg", O_RDWR | O_CREAT | O_TRUNC);
	fd = open(argv[1], O_RDONLY);
	if (argc < 2 || argc > 2 || fd < 0)
		exit (-1);
	line = NULL;
	init(&win);
	get_next_line(fd, &line);
	if (!ft_isnumstr(line))
		exit(-1);
	g_ants = ft_atoi(line);
	free(line);
	win->links = parsing(fd, &(win->graph), win->links);
	// win->links = parsing(fd, &(win->graph), win->links);
	print_matrix(my_fd, win->links);
	print_graph(win->graph);
	// print_variants(my_fd, win->graph);
	// dprintf(my_fd, "all good\n");
	draw_anthill(win, win->graph, win->links);
	mlx_hook(win->win_ptr, 2, 0, key_hook, win);
	mlx_hook(win->win_ptr, 17, 1L << 17, exit_x, 0);
	mlx_loop(win->mlx_ptr);
	return (0);
}
