#include "view.h"

void	init(t_win **win)
{
	*win = (t_win *)ft_memalloc(sizeof(t_win));
	(*win)->var = (t_brzhm *)ft_memalloc(sizeof(t_brzhm));
	(*win)->graph = NULL;
	(*win)->mlx_ptr = mlx_init();
	(*win)->win_ptr = mlx_new_window((*win)->mlx_ptr, WIDTH, HEIGTH, "Lem_in");
	(*win)->cell = 10;
	(*win)->move_side = 0;
	(*win)->move_up = 0;
}

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