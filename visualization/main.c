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

int		define_color(int ant)
{
	int			amount;
	int			color;
	static int	tmp;
	static int	step;

	amount = RGB;
	step = 8;
	while (ant >= amount)
	{
		amount *= RGB;
		step--;
	}
	if (tmp == 0)
		tmp = 0xFF000000 >> step;
	color = tmp;
	tmp = tmp >> step;
	dprintf(my_fd, "win->color %d, color step = %d\n", tmp, color);
	return (color);
}

void		define_ant(t_win *win, char *line)
{
	int		pos;
	int		num;
	char	*ptr;

	ptr = ft_strchr(line, '-');
	num = ft_atoi(line + 1);
	ptr += 1;
	pos = search_by_name(win->graph->graph, ptr, 0);
	if (win->ants[num - 1].num == 0)
	{
		win->ants[num - 1].num = num;
		dprintf(my_fd, "win->ants[num - 1].num = %d\n", win->ants[num - 1].num);
		win->ants[num - 1].color = define_color(num - 1);
		win->ants[num - 1].prev_room = 0;
		win->ants[num - 1].next_room = pos;
	}
	else
	{
		win->ants[num - 1].prev_room = win->ants[num - 1].next_room;
		win->ants[num - 1].next_room = pos;
	}
}

int			run(t_win *win)
{
	int		i;
	char	**arr;
	char	*line;

	while (get_next_line(0, &line) > 0)
	{
		dprintf(my_fd, "line = %s\n", line);
		if (ft_strchr(line, 'L'))
		{
			i = 0;
			win->flag = 0;
			arr = ft_strsplit(line, ' ');
			while (arr[i] != NULL)
			{
				define_ant(win, arr[i]);
				// dprintf(my_fd, "win->ants[0].num %d\n", win->ants[0].num)
				free(arr[i]);
				i++;
			}
			free(arr);
			// mlx_clear_window(win->mlx_ptr, win->win_ptr);
			ft_bzero(win->img, WIDTH * HEIGTH * 4);
			matrix_to_default(win);
			draw_anthill(win);
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
		ft_bzero(win->img, WIDTH * HEIGTH * 4);
		// mlx_destroy_image(win->mlx_ptr, win->img_ptr);
		// mlx_clear_window(win->mlx_ptr, win->win_ptr);
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
