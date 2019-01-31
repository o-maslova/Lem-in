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

void	define_delay(t_win *win)
{
	int nb;
	int tens;

	tens = 100000;
	nb = ft_digitnum(win->graph->ant_amount);
	win->delay = 600000 - (tens * nb);
	dprintf(my_fd, "delay = %d\n", win->delay);
}

void	make_rooms_arr(t_win *win)
{	
	int		i;
	int		j;
	t_vert	*tmp;

	i = 0;
	j = 0;
	tmp = win->graph->graph;
	win->rooms = (int **)ft_memalloc(sizeof(int *) * win->graph->rooms);
	while (tmp)
	{
		win->rooms[i] = (int *)ft_memalloc(sizeof(int) * 2);
		win->rooms[i][0] = tmp->x;
		win->rooms[i][1] = tmp->y;
		tmp = tmp->next;
		i++;
	}
}

void	init(t_win **w)
{
	(*w)->graph->graph = NULL;
	(*w)->graph->links = NULL;
	pars_data(0, &((*w)->graph));
	(*w)->var = (t_brzhm *)ft_memalloc(sizeof(t_brzhm));
	(*w)->color = 0xFF0000;
	(*w)->ants = (t_ant *)ft_memalloc(sizeof(t_ant) * ((*w)->graph->ant_amount + 1));
	make_rooms_arr(*w);
	define_delay(*w);
	(*w)->size_line = WIDTH;
	(*w)->bpp = 32;
	(*w)->endian = 0;
	(*w)->img_ptr = mlx_new_image((*w)->mlx_ptr, WIDTH, HEIGTH);
	(*w)->img =
	mlx_get_data_addr((*w)->img_ptr, &(*w)->bpp, &(*w)->size_line, &(*w)->endian);
	(*w)->cell = 10;
	(*w)->move_side = 0;
	(*w)->move_up = 0;
}

void		pixel_put_img(t_win *win, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGTH)
		*(int*)(win->img + ((x + y * WIDTH) * 4)) = color;
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

t_dot		search_by_pos(int **rooms, int pos)
{
	t_dot	dot;

	dot.x = rooms[pos][0];
	dot.y = rooms[pos][1];
	return (dot);
}