#include "lem_in.h"

void		clear_vertex(t_vert *vertex)
{
	t_link		*tmp;

	tmp = NULL;
	ft_strdel(&(vertex->name));
	free(vertex);
}

void		clear_graph(t_vert **graph)
{
	t_vert	*v_tmp;

	while (*graph)
	{
		ft_strdel(&((*graph)->name));
		v_tmp = *graph;
		*graph = (*graph)->next;
		clear_vertex(v_tmp);
	}
	free(*graph);
}

void		clear_matrix(int **links)
{
	int i;

	i = 0;
	while (i < g_amount)
	{
		free(links[i]);
		i++;
	}
	free(links);
}

void		clear_link(t_link **link)
{
	t_link *tmp;

	tmp = NULL;
	while (*link)
	{
		tmp = *link;
		free(*link);
		*link = tmp->next;
	}
}

void		clear_path(t_path **path)
{
	t_path *clear;

	clear = NULL;
	if (*path)
	{
		if ((*path)->next)
		{
			while ((*path)->next)
			{
				clear = (*path);
				free((*path)->path);
				free((*path));
				(*path) = clear->next;
			}
		}
		free((*path)->path);
		free(*path);
		*path = NULL;
	}
}