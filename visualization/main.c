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

int		define_color(t_win *win, int ant)
{
	int		i;
	int		amount;
	int		color;

	i = 0;
	amount = RGB;
	if (ant >= amount)
	{
		win->color.shift = 4;
		if (win->color.degree > 0 && win->color.degree < 8)
			win->color.shift = 1;
		while (i > 0)
			win->color.shift++;
		amount *= RGB;
	}
	color = win->color.tmp;
	win->color.tmp = win->color.tmp >> win->color.shift;
	if (win->color.tmp == 0)
		win->color.tmp = 0xFF0000 >> win->color.shift;
	dprintf(my_fd, "tmp %d, color = %d\n", win->color.tmp, color);
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
	if (win->ants[num - 1].num == -1)
	{
		win->ants[num - 1].num = num;
		// dprintf(my_fd, "win->ants[num - 1].num = %d\n", win->ants[num - 1].num);
		win->ants[num - 1].color = define_color(win, num - 1);
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
	int			j;
	static int	i;
	char		**steps;

	if (win->strings[i] == NULL)
		i = 0;
	dprintf(my_fd, "\n\n I = %d\n\n", i);
	while (win->strings[i] != NULL)
	{
		j = 0;
		steps = ft_strsplit(win->strings[i], ' ');
		while (steps[j] != NULL)
		{
			define_ant(win, steps[j]);
			free(steps[j]);
			j++;
		}
		matrix_to_default(win->graph->links, win->graph->rooms);
		draw_anthill(win);
		go(win);
		usleep(1200000);
		free(steps);
		i++;
		break ;
	}
	// free(win->strings);
	// mlx_clear_window(win->mlx_ptr, win->win_ptr);
	// ft_bzero(win->img, WIDTH * HEIGTH * 4);
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
	else if (keycode == 13)
		R_X += 0.2;
	else if (keycode == 1)
		R_X -= 0.2;
	else if (keycode == 2)
		R_Y += 0.2;
	else if (keycode == 0)
		R_Y -= 0.2;
	else if (keycode == 14)
		R_Z += 0.2;
	else if (keycode == 12)
		R_Z -= 0.2;
	if (keycode == 49)
	{
		// run(win);
		mlx_loop_hook(win->mlx_ptr, run, win);
	}
	ft_bzero(win->img, WIDTH * HEIGTH * 4);
	// set_ants_value(win->ants, win->graph->ant_amount);
	// mlx_destroy_image(win->mlx_ptr, win->img_ptr);
	// mlx_clear_window(win->mlx_ptr, win->win_ptr);
	// matrix_to_default(win->graph->links, win->graph->rooms);
	to_default(win);
	draw_anthill(win);	
	return (0);
}

void		read_ant_output(t_win *win)
{
	char *tmp;
	char *tmp2;
	char *line;

	tmp = NULL;
	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		// dprintf(my_fd, "line = %s\n", line);
		// line = ft_strcat(line, '\n');
		tmp2 = ft_strjoin(line, "\n");
		tmp = ft_strjoin(win->buff, tmp2);
		free(win->buff);
		win->buff = ft_strdup(tmp);
		// dprintf(my_fd, "win->buff = %s\n", win->buff);
		free(tmp);
		free(tmp2);
		free(line);
	}
	win->strings = ft_strsplit(win->buff, '\n');
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
	read_ant_output(win);
	draw_anthill(win);
	mlx_hook(win->win_ptr, 2, 0, key_hook, win);
	mlx_hook(win->win_ptr, 17, 1L << 17, exit_x, 0);
	mlx_loop(win->mlx_ptr);
	return (0);
}
