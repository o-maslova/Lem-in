#include "lem_in.h"

void		printf_this(int *arr)
{
	int i;

	i = 0;
	while (arr[i] != -1)
	{
		dprintf(g_fd, "%d  ", arr[i]);
		i++;
	}
}

void		print_path(t_link *path)
{
	t_link *tmp;
	
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

void		print_graph(t_graph *graph)
{
	t_vert		*tmp;

	tmp = graph->graph;
	while (tmp)
	{
		printf("\nname = %s, pos = %d, (%d, %d)\n", tmp->name, tmp->pos, tmp->x, tmp->y);
		if (tmp->is_start == 1)
			printf("IS START\n");
		if (tmp->is_end == 1)
			printf("IS END\n");
		tmp = tmp->next;
	}
}