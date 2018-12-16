#include "lem_in.h"

void		print_path(t_link *path)
{
	int i;
	t_link *tmp;
	
	i = 0;
	tmp = path;
	while (tmp)
	{
		// dprintf(g_fd, "\nPATH #%d\n", i + 1);
		dprintf(g_fd, "%d\n", tmp->pos);
		tmp = tmp->next;
	}
}

void		print_variants(t_path *path)
{
	int i;
	t_path *tmp;

	tmp = path;
	while (tmp)
	{
		i = -1;
		while (++i < tmp->path_val)
			dprintf(g_fd, "%d\n", tmp->path[i]);
		dprintf(g_fd, "\n");
		tmp = tmp->next;
	}
}

void		print_matrix(int **links)
{
	int i;
	int j;

	i = 0;
	dprintf(g_fd, " ");
	while (i < g_amount)
	{
		dprintf(g_fd, "%5d", i++);
	}
	dprintf(g_fd, "\n");
	i = 0;
	while (i < g_amount)
	{
		j = 0;
		while (j < g_amount)
		{
			if (j == 0)
				dprintf(g_fd, "%d", i);
			dprintf(g_fd, "%5d", links[i][j]);
			j++;
		}
		dprintf(g_fd, "\n");
		i++;
	}
}

void		print_graph(t_vert *graph)
{
	t_vert		*tmp;

	tmp = graph;
	while (tmp)
	{
		ft_printf("\nname = %s, pos = %d, (%d, %d)\n", tmp->name, tmp->pos, tmp->x, tmp->y);
		if (tmp->is_start == 1)
			ft_printf("IS START\n");
		if (tmp->is_end == 1)
			ft_printf("IS END\n");
		tmp = tmp->next;
	}
}