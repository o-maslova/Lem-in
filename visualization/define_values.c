/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_values.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 13:59:21 by omaslova          #+#    #+#             */
/*   Updated: 2018/11/24 13:59:23 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "view.h"

void	for_better_visual(t_win *win)
{
	if (VIEW_COLUMN > 50)
	{
		win->cell = 10;
		win->value = 6;
	}
	else if (VIEW_COLUMN < 20)
	{
		win->cell = 32;
		win->value = 5;
	}
	else
	{
		win->cell = 20;
		win->value = 3;
	}
}

void	init(t_win *win)
{
	win->mlx_ptr = mlx_init();
	win->win_ptr = mlx_new_window(win->mlx_ptr, HEIGTH, WIDTH, "Filler");
	win->size_line = WIDTH;
	win->bpp = 32;
	win->endian = 0;
	win->img_ptr = mlx_new_image(win->mlx_ptr, HEIGTH, WIDTH);
	win->img =
	mlx_get_data_addr(win->img_ptr, &win->bpp, &win->size_line, &win->endian);
}

int		allocate_mem(t_win *win, char *line, int i)
{
	line += 8;
	VIEW_ROW = ft_atoi(line);
	line += ft_digitnum(VIEW_ROW);
	VIEW_COLUMN = ft_atoi(line);
	win->matrix = (char **)ft_memalloc(sizeof(char *) * VIEW_ROW);
	while (++i < VIEW_ROW)
		win->matrix[i] = (char *)ft_memalloc(sizeof(char) * VIEW_COLUMN);
	for_better_visual(win);
	win->width = VIEW_COLUMN * CELL_SIZE + (CELL_SIZE * 20);
	win->heigth = VIEW_COLUMN * CELL_SIZE + (CELL_SIZE * 20);
	return (0);
}

int		set_matrix(t_win *win)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = 0;
	while (i < VIEW_ROW)
	{
		j = -1;
		k = 4;
		get_next_line(g_fd_m, &tmp);
		while (++j < VIEW_COLUMN)
		{
			tmp[k] = ft_tolower(tmp[k]);
			win->matrix[i][j] = tmp[k];
			++k;
		}
		free(tmp);
		++i;
	}
	return (i);
}
