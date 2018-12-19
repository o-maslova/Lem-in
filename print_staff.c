#include "lem_in.h"

void		print_path(t_link *path)
{
	int i;
	t_link *tmp;
	
	i = 0;
	tmp = path;
	// dprintf(g_fd, "value of path: %d\n", tmp->path_val);
	while (tmp)
	{
		dprintf(g_fd, "%d\n", tmp->pos);
		tmp = tmp->next;
	}
}

void		print_variants(int fd, t_path *path)
{
	int i;
	t_path *tmp;

	tmp = path;
	while (tmp)
	{
		i = -1;
		dprintf(fd, "NEW PATH\n");
		dprintf(fd, "value of path: %d\n", tmp->path_val);
		while (++i < tmp->path_val)
			dprintf(fd, "%d\n", tmp->path[i]);
		dprintf(fd, "\n");
		tmp = tmp->next;
	}
}

void		print_matrix(int fd, t_graph *graph)
{
	int i;
	int j;

	i = 0;
	dprintf(fd, " ");
	while (i < graph->rooms)
	{
		dprintf(fd, "%5d", i++);
	}
	dprintf(fd, "\n");
	i = 0;
	while (i < graph->rooms)
	{
		j = 0;
		while (j < graph->rooms)
		{
			if (j == 0)
				dprintf(fd, "%d", i);
			dprintf(fd, "%5d", graph->links[i][j]);
			j++;
		}
		dprintf(fd, "\n");
		i++;
	}
}

void		print_graph(t_vert *graph)
{
	t_vert		*tmp;

	tmp = graph;
	while (tmp)
	{
		ft_printf("\npos = %d, (%d, %d)\n", tmp->pos, tmp->x, tmp->y);
		if (tmp->is_start == 1)
			ft_printf("IS START\n");
		if (tmp->is_end == 1)
			ft_printf("IS END\n");
		tmp = tmp->next;
	}
}