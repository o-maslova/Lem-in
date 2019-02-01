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

void		matrix_to_default(int **links, int rooms)
{
	int i;
	int j;

	i = 0;
	while (i < rooms)
	{
		j = 0;
		while (j < rooms)
		{
			if (links[i][j] == -1)
				links[i][j] = 1;
			j++;
		}
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
	win->mod_rooms = (int **)ft_memalloc(sizeof(int *) * win->graph->rooms);
	win->edge.min_x = tmp->x;
	win->edge.min_y = tmp->y;
	win->edge.max_x = tmp->x;
	win->edge.max_y = tmp->y;
	while (tmp)
	{
		if (tmp->x < win->edge.min_x)
			win->edge.min_x = tmp->x;
		if (tmp->y < win->edge.min_y)
			win->edge.min_y = tmp->y;
		if (tmp->x > win->edge.max_x)
			win->edge.max_x = tmp->x;
		if (tmp->y > win->edge.max_y)
			win->edge.max_y = tmp->y;
		win->rooms[i] = (int *)ft_memalloc(sizeof(int) * 2);
		win->mod_rooms[i] = (int *)ft_memalloc(sizeof(int) * 2);
		win->rooms[i][0] = tmp->x;
		win->rooms[i][1] = tmp->y;
		win->mod_rooms[i][0] = win->rooms[i][0];
		win->mod_rooms[i][1] = win->rooms[i][1];
		tmp = tmp->next;
		i++;
	}
}

void	set_ants_value(t_ant *ants, int lim)
{
	int i;

	i = 0;
	while (i < lim + 1)
	{
		ants[i].num = -1;
		ants[i].color = 0;
		ants[i].prev_room = 0;
		ants[i].next_room = 0;
		i++;
	}

}

void	to_default(t_win *win)
{
	int i;

	i = 0;
	while (i < win->graph->rooms)
	{
		win->mod_rooms[i][0] = win->rooms[i][0];
		win->mod_rooms[i][1] = win->rooms[i][1];
		i++;
	}
	set_ants_value(win->ants, win->graph->ant_amount);
	matrix_to_default(win->graph->links, win->graph->rooms);
	win->color.degree = ft_degree_of_three(win->graph->ant_amount);
	win->color.shift = 8;
	win->color.tmp = 0xFF0000;
}

void	define_center(t_win *win)
{
	win->cen_x = ((win->edge.max_x - win->edge.min_x) * CELL_SIZE) / 2;
	win->cen_y = ((win->edge.max_y - win->edge.min_y) * CELL_SIZE) / 2;
}

void	init(t_win **w)
{
	(*w)->graph->graph = NULL;
	(*w)->graph->links = NULL;
	pars_data(0, &((*w)->graph));
	(*w)->var = (t_brzhm *)ft_memalloc(sizeof(t_brzhm));
	(*w)->color.color = 0xFF0000;
	(*w)->ants = (t_ant *)ft_memalloc(sizeof(t_ant) * ((*w)->graph->ant_amount + 1));
	make_rooms_arr(*w);
	define_delay(*w);
	define_center(*w);
	(*w)->color.degree = ft_degree_of_three((*w)->graph->ant_amount);
	(*w)->color.shift = 8;
	(*w)->color.tmp = 0xFF0000;
	(*w)->buff = NULL;
	(*w)->angle.ang_x = 2;
	(*w)->angle.ang_y = 0.5;
	(*w)->angle.ang_z = 0;
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

int			*search_by_pos(int **rooms, int pos)
{
	int		*room;

	room = (int *)ft_memalloc(sizeof(int) * 2);
	room[0] = rooms[pos][0];
	room[1] = rooms[pos][1];
	return (room);
}