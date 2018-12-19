#include "view.h"

void	init(int fd, t_win **win)
{
	*win = (t_win *)ft_memalloc(sizeof(t_win));
	(*win)->var = (t_brzhm *)ft_memalloc(sizeof(t_brzhm));
	(*win)->mlx_ptr = mlx_init();
	(*win)->win_ptr = mlx_new_window((*win)->mlx_ptr, WIDTH, HEIGTH, "Lem_in");
	(*win)->size_line = WIDTH;
	(*win)->bpp = 32;
	(*win)->endian = 0;
	// (*win)->img_ptr = mlx_new_image((*win)->mlx_ptr, WIDTH, HEIGTH);
	// (*win)->img =
	// mlx_get_data_addr((*win)->img_ptr, &(*win)->bpp, &(*win)->size_line, &(*win)->endian);
	(*win)->graph = NULL;
	(*win)->links = parsing(fd, &((*win)->graph), (*win)->links);
	(*win)->cell = 3;
	(*win)->move_side = 0;
	(*win)->move_up = 0;
	(*win)->min_up = ((*win)->graph->y * (*win)->cell) + ((*win)->cell / 2) + (*win)->move_up;
	(*win)->min_down = ((*win)->graph->y * (*win)->cell) + ((*win)->cell / 2) + (*win)->move_up;
	(*win)->min_left = ((*win)->graph->x * (*win)->cell) + ((*win)->cell / 2) + (*win)->move_side;
	(*win)->min_right = ((*win)->graph->x * (*win)->cell) + ((*win)->cell / 2) + (*win)->move_side;
}

void		pixel_put_img(t_win *win, int x, int y, int colour)
{
	if (x < HEIGTH || y < WIDTH)
	{
		colour = mlx_get_color_value(win->mlx_ptr, colour);
		ft_memcpy(win->img + 4 * WIDTH * y + x * 4, &colour, sizeof(int));
	}
}

// void		min_to_default(t_win *win)
// {

// }

void		matrix_to_default(int **links)
{
	int i;
	int j;

	i = 0;
	while (i < g_amount)
	{
		j = 0;
		while (j < g_amount)
		{
			if (links[i][j] == -1)
				links[i][j] = 1;
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