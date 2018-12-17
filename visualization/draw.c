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

int			exit_x(void *par)
{
	par = NULL;
	exit(1);
	return (0);
}

void	init(t_win *win)
{
	win->mlx_ptr = mlx_init();
	win->win_ptr = mlx_new_window(win->mlx_ptr, HEIGTH, WIDTH, "Lem_in");
	win->size_line = WIDTH;
	win->bpp = 32;
	win->endian = 0;
	win->img_ptr = mlx_new_image(win->mlx_ptr, HEIGTH, WIDTH);
	win->img =
	mlx_get_data_addr(win->img_ptr, &win->bpp, &win->size_line, &win->endian);
}

void	pixel_put_img(t_win *win, int x, int y, int colour)
{
	if (x < HEIGTH || y < WIDTH)
	{
		colour = mlx_get_color_value(win->mlx_ptr, colour);
		ft_memcpy(win->img + 4 * WIDTH * y + x * 4, &colour, sizeof(int));
	}
}

void		draw_links(t_win *win, t_vert *graph, int **links)
{
	int		i;
	int		j;
	// int		tmp[2];
	t_vert	first;
	t_vert	second;

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
				first.x *= CELL_SIZE;
				first.x = first.x + (CELL_SIZE / 2);
				second.x *= CELL_SIZE;
				second.x = second.x + (CELL_SIZE / 2);
				first.y *= CELL_SIZE;
				first.y = first.y + (CELL_SIZE / 2);
				second.y *= CELL_SIZE;
				second.y = second.y + (CELL_SIZE / 2);
				dprintf(my_fd, "first_x = %d, first_y = %d\n", first.x, first.y);
				dprintf(my_fd, "second_x = %d, second_y = %d\n", second.x, second.y);
				brznh_algo(win, second, first);
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
	while (i < x + CELL_SIZE)
	{
		j = y;
		while (j < y + CELL_SIZE)
		{
			mlx_pixel_put(win->mlx_ptr, win->win_ptr, i, j, 0xFFFFFF);
			j++;
		}
		i++;
	}
	// dprintf(my_fd, "\n");
	dprintf(my_fd, "i = %d, j = %d\n", i, j);
	dprintf(my_fd, "\n");
}

void		draw_anthill(t_win *win, t_vert *graph, int **links)
{
	int		x;
	int		y;
	t_vert	*tmp;

	x = 0;
	y = 0;
	tmp = graph;
	while (tmp)
	{
		// dprintf(my_fd, "x = %d, y = %d\n", tmp->x, tmp->y);
		x = tmp->x * CELL_SIZE;
		y = tmp->y * CELL_SIZE;
		draw_room(win, x, y);
		// pixel_put_img(win, tmp->x, tmp->y, 0xFFFFFF);
		tmp = tmp->next;
	}
	draw_links(win, graph, links);
}

static int	key_hook(int keycode, t_win *win)
{
	if (keycode == 53)
	{
		// ft_arrdel(win->matrix, VIEW_ROW);
		free(win);
		mlx_destroy_window(win->mlx_ptr, win->win_ptr);
		exit(0);
	}
	// else if (keycode == 49)
	// {
	// 	mlx_loop_hook(win->mlx_ptr, game, win);
	// }
	return (0);
}

int			main(int argc, char **argv)
{
	int		fd;
	int		**links;
	char	*line;
	t_win	*win;
	t_vert	*graph;

	my_fd = open("logg", O_RDWR | O_CREAT | O_TRUNC);
	fd = open(argv[1], O_RDONLY);
	if (argc < 2 || argc > 2 || fd < 0)
		exit (-1);
	line = NULL;
	links = NULL;
	win = (t_win *)ft_memalloc(sizeof(t_win));
	win->var = (t_brzhm *)ft_memalloc(sizeof(t_brzhm));
	init(win);
	get_next_line(fd, &line);
	if (!ft_isnumstr(line))
		error_handling(7, NULL, &graph);
	g_ants = ft_atoi(line);
	free(line);
	links = parsing(fd, &graph, links);
	print_matrix(my_fd, links);
	print_graph(graph);
	// print_variants(my_fd, graph);
	// dprintf(my_fd, "all good\n");
	draw_anthill(win, graph, links);
	// mlx_string_put(win->mlx_ptr, win->win_ptr, win->row + PAD,
	// VIEW_ROW * CELL_SIZE + PAD * 2 + CELL_SIZE * VAL, 0xFFD700,
	// "Press SPACE to start the game");
	mlx_hook(win->win_ptr, 2, 0, key_hook, win);
	mlx_hook(win->win_ptr, 17, 1L << 17, exit_x, 0);
	mlx_loop(win->mlx_ptr);
	return (0);
}
