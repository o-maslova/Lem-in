#include "view.h"

void		print_matrix(int fd, t_graph graph)
{
	int i;
	int j;

	i = 0;
	dprintf(fd, " ");
	while (i < graph.rooms)
	{
		dprintf(fd, "%5d", i++);
	}
	dprintf(fd, "\n");
	i = 0;
	while (i < graph.rooms)
	{
		j = 0;
		while (j < graph.rooms)
		{
			if (j == 0)
				dprintf(fd, "%d", i);
			dprintf(fd, "%5d", graph.links[i][j]);
			j++;
		}
		dprintf(fd, "\n");
		i++;
	}
}

void	define_steps(t_win *win)
{
	int nb;
	int tmp;
	int tens;
	int res;

	res = 1;
	tens = 10000000;
	tmp = ft_digitnum(win->graph->ant_amount);
	nb = tmp;
	while (tmp-- > 0)
		res = res * 10;
	tens -= res;
	win->color_step = tens;
	dprintf(my_fd, "color step = %d\n", win->color_step);
	tens = 100000;
	win->delay = 600000 - (tens * nb);
	dprintf(my_fd, "delay = %d\n", win->delay);
}

void	init(t_win **win)
{
	(*win)->graph->graph = NULL;
	(*win)->graph->links = NULL;
	pars_data(0, &((*win)->graph));
	(*win)->var = (t_brzhm *)ft_memalloc(sizeof(t_brzhm));
	define_steps(*win);
	// (*win)->size_line = WIDTH;
	// (*win)->bpp = 32;
	// (*win)->endian = 0;
	// (*win)->img_ptr = mlx_new_image((*win)->mlx_ptr, WIDTH, HEIGTH);
	// (*win)->img =
	// mlx_get_data_addr((*win)->img_ptr, &(*win)->bpp, &(*win)->size_line, &(*win)->endian);
	(*win)->cell = 10;
	(*win)->move_side = 0;
	(*win)->move_up = 0;
	(*win)->min_up = ((*win)->graph->graph->y * (*win)->cell) + ((*win)->cell / 2) + (*win)->move_up;
	(*win)->min_down = ((*win)->graph->graph->y * (*win)->cell) + ((*win)->cell / 2) + (*win)->move_up;
	(*win)->min_left = ((*win)->graph->graph->x * (*win)->cell) + ((*win)->cell / 2) + (*win)->move_side;
	(*win)->min_right = ((*win)->graph->graph->x * (*win)->cell) + ((*win)->cell / 2) + (*win)->move_side;
}

void		pixel_put_img(t_win *win, int x, int y, int colour)
{
	if (x < HEIGTH || y < WIDTH)
	{
		colour = mlx_get_color_value(win->mlx_ptr, colour);
		ft_memcpy(win->img + 4 * WIDTH * y + x * 4, &colour, sizeof(int));
	}
}

void		matrix_to_default(t_win *win)
{
	int i;
	int j;

	i = 0;
	while (i < win->graph->rooms)
	{
		j = 0;
		while (j < win->graph->rooms)
		{
			if (win->graph->links[i][j] == -1)
				win->graph->links[i][j] = 1;
			j++;
		}
		i++;
	}
}

t_dot		search_by_pos(t_vert *graph, int pos)
{
	t_vert	*tmp;
	t_dot	*dot;

	dot = NULL;
	tmp = NULL;
	if (graph)
	{
		tmp = graph;
		while (tmp)
		{
			if (tmp->pos == pos)
			{
				dot = (t_dot *)ft_memalloc(sizeof(t_dot));
				dot->x = tmp->x;
				dot->y = tmp->y;
				return (*dot);
			}
			tmp = tmp->next;
		}
	}
	return (*dot);
}